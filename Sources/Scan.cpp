#include <iostream>
#include <Windows.h>
#include <Stdio.h>
#include <Conio.h>
#include <WinBio.h>

using namespace std;

#pragma comment(lib, "Winbio.lib")
#include "../Headers/Scan.h"

bool GetCurrentUserIdentity(__inout PWINBIO_IDENTITY Identity)
{
	SetConsoleOutputCP(1251);

	HRESULT hr = S_OK;
	HANDLE tokenHandle = NULL;
	DWORD bytesReturned = 0;
	struct {
		TOKEN_USER tokenUser;
		BYTE buffer[SECURITY_MAX_SID_SIZE];
	} tokenInfoBuffer;

	// Обнуляем входной идентификатор и указываем тип
	ZeroMemory(Identity, sizeof(WINBIO_IDENTITY));
	Identity->Type = WINBIO_ID_TYPE_NULL;

	// Open the access token associated with the
	// current process
	if (!OpenProcessToken(
		GetCurrentProcess(),            // Process handle
		TOKEN_READ,                     // Read access only
		&tokenHandle))                  // Access token handle
	{
		DWORD win32Status = GetLastError();
		cout << "Ошибка сканера" << endl;
		hr = HRESULT_FROM_WIN32(win32Status);
		goto e_Exit;
	}

	// Zero the tokenInfoBuffer structure.
	ZeroMemory(&tokenInfoBuffer, sizeof(tokenInfoBuffer));

	// Retrieve information about the access token. In this case,
	// retrieve a SID.
	if (!GetTokenInformation(
		tokenHandle,                    // Access token handle
		TokenUser,                      // User for the token
		&tokenInfoBuffer.tokenUser,     // Buffer to fill
		sizeof(tokenInfoBuffer),        // Size of the buffer
		&bytesReturned))                // Size needed
	{
		DWORD win32Status = GetLastError();
		cout << "Невозможно получить информацию по отпечатку" << endl;
		hr = HRESULT_FROM_WIN32(win32Status);
		goto e_Exit;
	}

	// Copy the SID from the tokenInfoBuffer structure to the
	// WINBIO_IDENTITY structure. 
	CopySid(
		SECURITY_MAX_SID_SIZE,
		Identity->Value.AccountSid.Data,
		tokenInfoBuffer.tokenUser.User.Sid
	);

	// Specify the size of the SID and assign WINBIO_ID_TYPE_SID
	// to the type member of the WINBIO_IDENTITY structure.
	Identity->Value.AccountSid.Size = GetLengthSid(tokenInfoBuffer.tokenUser.User.Sid);
	Identity->Type = WINBIO_ID_TYPE_SID;

e_Exit:

	if (tokenHandle != NULL)
	{
		CloseHandle(tokenHandle);
	}

	if (FAILED(hr))
		return false;
	else
		return true;
}

bool Verify()
{
	SetConsoleOutputCP(1251);
	HRESULT hr = S_OK;										// Переменная состояния
	WINBIO_SESSION_HANDLE sessionHandle = NULL;				// Указатель на дескриптор
	WINBIO_UNIT_ID unitId = 0;
	WINBIO_REJECT_DETAIL rejectDetail = 0;
	WINBIO_IDENTITY identity = { 0 };
	BOOLEAN match = FALSE;

	// Find the identity of the user.
	hr = GetCurrentUserIdentity(&identity);
	if (FAILED(hr))
	{
		cout << "Пользователь не найден" << endl;
		goto e_Exit;
	}

	// Начало сессии
	hr = WinBioOpenSession(
		WINBIO_TYPE_FINGERPRINT,    // Работа с отпечатками пальца
		WINBIO_POOL_SYSTEM,         // Выбор объектного пула, который будет использоваться в сессии. В данном случае используется системный пул
		WINBIO_FLAG_DEFAULT,        // Флаг, обеспечивающий разный уровень доступа к информации по отпечатку
		NULL,                       // Указатель на массив идентефикаторов, используемых в сессии. При работе с системный пулом, указывается NULL
		0,                          // Количество отпечатков, испотзуемых в сесии. При работе с системный пулом, указывается NULL
		WINBIO_DB_DEFAULT,                       // 
		&sessionHandle              // Указатель на дескриптор
	);
	if (FAILED(hr))
	{
		cout << "Неудачная попытка начала работы" << endl;
		goto e_Exit;
	}

	// Верефикация отпечатка пальца
	cout << "Отсканируйте отпечаток" << endl;
	hr = WinBioVerify(
		sessionHandle,
		&identity,
		WINBIO_SUBTYPE_ANY,
		&unitId,
		&match,
		&rejectDetail
	);
	if (!FAILED(hr))
			cout << "Успешное совпадение" << endl;
		else if (hr == WINBIO_E_NO_MATCH)
			cout << "Совпвдений не найдено" << endl;
		else if (hr == WINBIO_E_BAD_CAPTURE)
			cout << "Неудачное сканирование" << endl;
	Sleep(1000);


e_Exit:
	if (sessionHandle != NULL)
	{
		WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}

	if (FAILED(hr))
		return false;
	else
		return true;
}

bool Scan()
{
	SetConsoleOutputCP(1251);
	for (int n = 5; n > 0; n--)
	{
		cout << "Осталось " << n << " попыток" << endl;
		if (Verify())
			return true;
		system("cls");
	}
	cout << "Для разблокировки введите '111': ";
	int a;
	cin >> a;
	if (a == 111)
		return true;
	return false;
}