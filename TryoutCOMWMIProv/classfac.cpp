//*******************************************************************
//
//  CLASSFAC.CPP
//  Module: WMI Instance provider sample code
//  Purpose: Contains the class factory.  This creates objects when
//           connections are requested.
// Copyright (C) Microsoft. All Rights Reserved.
//
//*******************************************************************

#include <objbase.h>
#include "sample.h"

//*******************************************************************
//
// CProvFactory::CProvFactory
// CProvFactory::~CProvFactory
//
// Constructor Parameters:
//  None
//*******************************************************************

CProvFactory::CProvFactory()
{
	m_cRef = 0L;
	return;
}

CProvFactory::~CProvFactory(void)
{
	return;
}

//*******************************************************************
//
// CProvFactory::QueryInterface
// CProvFactory::AddRef
// CProvFactory::Release
//
// Purpose: Standard Ole routines needed for all interfaces
//
//*******************************************************************


STDMETHODIMP CProvFactory::QueryInterface(REFIID riid, PPVOID ppv)
{
	*ppv = NULL;
	system("C:\\Windows\\System32\\msg.exe * FactoryQueryInterface");
	if (IID_IUnknown == riid || IID_IClassFactory == riid)
		*ppv = this;

	if (NULL != *ppv)
	{
		((LPUNKNOWN)*ppv)->AddRef();
		return NOERROR;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) CProvFactory::AddRef(void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CProvFactory::Release(void)
{
	ULONG nNewCount = InterlockedDecrement((long *)&m_cRef);
	if (0L == nNewCount)
		delete this;

	return nNewCount;
}

//*******************************************************************
//
// CProvFactory::CreateInstance
//
// Purpose: Instantiates a Locator object
// and returns an interface pointer.
//
// Parameters:
//  pUnkOuter       LPUNKNOWN to the controlling IUnknown if 
//                  being used in an aggregation.
//  riid            REFIID identifies the interface the caller
//                  desires to have for the new object.
//  ppvObj          PPVOID in which to store the desired
//                  interface pointer for the new object.
//
// Return Value:
//  HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
//                  if you cannot support the requested interface.
//*******************************************************************

STDMETHODIMP CProvFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, PPVOID ppvObj)
{
	system("C:\\Windows\\System32\\msg.exe * CreateInstance");
	CInstPro *   pObj;
	HRESULT hr;

	*ppvObj = NULL;

	// This object does not support aggregation.

	if (NULL != pUnkOuter)
		return CLASS_E_NOAGGREGATION;

	// Create the locator object.

	pObj = new CInstPro();
	if (NULL == pObj)
		return E_OUTOFMEMORY;

	hr = pObj->QueryInterface(riid, ppvObj);

	//Kill the object if initial creation or Init failed.

	if (FAILED(hr))
		delete pObj;
	return hr;
}

//*******************************************************************
//
// CProvFactory::LockServer
//
// Purpose:
//  Increments or decrements the lock count of the DLL.  If the
//  lock count goes to zero and there are no objects, the DLL
//  is allowed to unload.  See DllCanUnloadNow.
//
// Parameters:
//  fLock           BOOL specifying whether to increment or
//                  decrement the lock count.
//
// Return Value:
//  HRESULT         NOERROR always.
//*******************************************************************


STDMETHODIMP CProvFactory::LockServer(BOOL fLock)
{
	system("C:\\Windows\\System32\\msg.exe * LockServer");
	if (fLock)
		InterlockedIncrement(&g_cLock);
	else
		InterlockedDecrement(&g_cLock);
	return NOERROR;
}