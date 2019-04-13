#pragma once
#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include "StringUtilities.h"

void SendRequest(LPSTR pszOutBuffer);
