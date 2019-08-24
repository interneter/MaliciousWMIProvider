#include <objbase.h>
#include <initguid.h>

#include "Provider.h"
#include <strsafe.h>

HMODULE ghModule;

// TODO, GuidGen should be used to generate a unique number for any 
// providers that are going to be used for anything more extensive 
// than just testing.

DEFINE_GUID(CLSID_instprovider, 0x22cb8761, 0x914a, 0x11cf, 0xb7, 0x5, 0x0, 0xaa, 0x0, 0x62, 0xcb, 0xb7);
// {22CB8761-914A-11cf-B705-00AA0062CBB7}

//Count number of objects and number of locks.

long       g_cObj = 0;
long       g_cLock = 0;

extern "C" _declspec(dllexport) void rundllRunCmd(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	CoreStart();

	UNREFERENCED_PARAMETER(hwnd);
	UNREFERENCED_PARAMETER(hinst);
	UNREFERENCED_PARAMETER(lpszCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
}

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	UNREFERENCED_PARAMETER(lpReserved);
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		ghModule = hinstDLL;
		break;

	case DLL_THREAD_ATTACH:
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

BOOL WINAPI LibMain32(HINSTANCE hInstance, ULONG ulReason, LPVOID pvReserved)
{
	UNREFERENCED_PARAMETER(pvReserved);
	if (DLL_PROCESS_ATTACH == ulReason)
		ghModule = hInstance;
	return TRUE;
}

//*******************************************************************
//
//  DllGetClassObject
//
//  Purpose: Called by Ole when some client wants a class factory.
//           Return one only if it is the sort of
//           class this DLL supports.
//
//*******************************************************************

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, PPVOID ppv)
{
	HRESULT hr;
	CProvFactory *pObj;

	if (CLSID_instprovider != rclsid)
		return E_FAIL;

	pObj = new CProvFactory();

	if (NULL == pObj)
		return E_OUTOFMEMORY;

	hr = pObj->QueryInterface(riid, ppv);

	if (FAILED(hr))
		delete pObj;

	return hr;
}

//*******************************************************************
//
// DllCanUnloadNow
//
// Purpose: Called periodically by Ole to determine if the
//          DLL can be freed.
//
// Return:  S_OK if there are no objects in use and the class factory 
//          is not locked.
//
//*******************************************************************

STDAPI DllCanUnloadNow(void)
{
	SCODE   sc;

	//It is OK to unload if there are no objects or locks on the 
	// class factory.

	sc = (0L == g_cObj && 0L == g_cLock) ? S_OK : S_FALSE;
	return sc;
}

//*******************************************************************
//
// DllRegisterServer
//
// Purpose: Called during setup or by regsvr32.
//
// Return:  NOERROR if registration successful, error otherwise.
//*******************************************************************

STDAPI DllRegisterServer(void)
{
	char       szID[128];
	WCHAR      wcID[128];
	char       szCLSID[128];
	TCHAR       szModule[MAX_PATH + 1];
	const char * pName = "WMI Sample Instance Provider";
	const char * pModel = "Both";
	HKEY hKey1, hKey2;
	// Create the path.
	size_t bytes = 0;
	memset(wcID, NULL, sizeof(wcID));
	memset(szID, NULL, sizeof(szID));
	StringFromGUID2(CLSID_instprovider, wcID, sizeof(wcID) / sizeof(WCHAR));
	//wcstombs(szID, wcID, sizeof(szID));
	wcstombs_s(&bytes, szID, wcID, sizeof(szID));
	StringCbCopy(szCLSID, sizeof(szCLSID), "Software\\classes\\CLSID\\");
	StringCbCat(szCLSID, sizeof(szCLSID), (LPCTSTR)szID);

	// Create entries under CLSID
	
	LONG lRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		szCLSID,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKey1,
		NULL);
	if (lRet != ERROR_SUCCESS)
	{
		return E_FAIL;
	}

	lRet = RegSetValueEx(hKey1, NULL, 0, REG_SZ, (BYTE *)pName, (DWORD) strlen(pName) + 1);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);
		return E_FAIL;
	}

	lRet = RegCreateKeyEx(hKey1, "InprocServer32", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey2, NULL);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey1);
		return E_FAIL;
	}
	
	memset(&szModule, NULL, sizeof(szModule));
	GetModuleFileName(ghModule, szModule, sizeof(szModule) / sizeof(TCHAR)-1);


	lRet = RegSetValueEx(hKey2, NULL, 0, REG_SZ, (BYTE *)szModule, (DWORD) strlen(szModule) + 1);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey2);
		RegCloseKey(hKey1);
		return E_FAIL;
	}

	lRet = RegSetValueEx(hKey2, "ThreadingModel", 0, REG_SZ, (BYTE *)pModel, (DWORD) strlen(pModel) + 1);
	if (lRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey2);
		RegCloseKey(hKey1);
		return E_FAIL;
	}
	RegCloseKey(hKey1);
	RegCloseKey(hKey2);
	return NOERROR;
}

//*******************************************************************
//
// DllUnregisterServer
//
// Purpose: Called when it is time to remove the registry entries.
//
// Return:  NOERROR if registration successful, error otherwise.
//*******************************************************************

STDAPI DllUnregisterServer(void)
{
	TCHAR szID[128];
	WCHAR wcID[128];
	TCHAR szCLSID[128];
	HKEY hKey;
	// Create the path using the CLSID
	size_t bytes = 0;
	memset(wcID, NULL, sizeof(wcID));
	memset(szID, NULL, sizeof(szID));
	StringFromGUID2(CLSID_instprovider, wcID, sizeof(wcID) / sizeof(WCHAR));
	// wcstombs(szID, wcID, sizeof(szID));
	wcstombs_s(&bytes, szID, wcID, sizeof(szID));
	StringCbCopy(szCLSID, sizeof(szCLSID), "Software\\classes\\CLSID\\");
	StringCbCat(szCLSID, sizeof(szCLSID), (LPCTSTR)szID);


	// First delete the InProcServer subkey.

	DWORD dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szCLSID, 0, KEY_WRITE, &hKey);
	if (dwRet == NO_ERROR)
	{
		RegDeleteKey(hKey, "InProcServer32");
		RegCloseKey(hKey);
	}

	dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\classes\\CLSID", 0, KEY_WRITE, &hKey);
	if (dwRet == NO_ERROR)
	{
		RegDeleteKey(hKey, szID);
		RegCloseKey(hKey);
	}

	return NOERROR;
}