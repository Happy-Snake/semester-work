#pragma once
#include <Stdio.h>
#include <Conio.h>
#include <WinBio.h>

bool GetCurrentUserIdentity(__inout PWINBIO_IDENTITY Identity);

bool Verify();

bool Scan();