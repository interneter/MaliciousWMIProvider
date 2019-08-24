#pragma once

/**********Includes**********/

#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include "StringUtilities.h"
#include "Logger.h"
#include "Globals.h"

#define COMM_PORT 4443
#define COMM_ADDRESS _T("127.0.0.1")
#define COMM_HTTP_USERAGENT _T("Testing")

/**********Declarations**********/

void SendRequest(LPSTR *totalBuffer);
