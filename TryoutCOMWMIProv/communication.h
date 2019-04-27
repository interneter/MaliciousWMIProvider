#pragma once

/**********Includes**********/

#include <windows.h>
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include "StringUtilities.h"

/**********Declarations**********/

void SendRequest(LPSTR *totalBuffer);
