//*******************************************************************
//  sample.h
//  WMI Instance provider sample code
//
// Copyright (C) Microsoft. All Rights Reserved.
//
//*******************************************************************

#ifndef _sample_H_
#define _sample_H_

#include <wbemprov.h>
#pragma comment(lib, "wbemuuid.lib")

typedef LPVOID * PPVOID;

// Provider interfaces are provided by objects of this class

class CInstPro : public IWbemServices, public IWbemProviderInit, public IWbemEventProvider
{
protected:
	ULONG m_cRef;         //Object reference count
	IWbemServices* m_pNamespace;
public:
	CInstPro(BSTR ObjectPath = NULL, BSTR User = NULL, BSTR Password = NULL, IWbemContext * pCtx = NULL);
	~CInstPro(void);

	//Non-delegating object IUnknown

	STDMETHODIMP QueryInterface(REFIID, PPVOID);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	//IWbemProviderInit

	HRESULT STDMETHODCALLTYPE Initialize(
		/* [in] */ LPWSTR pszUser,
		/* [in] */ LONG lFlags,
		/* [in] */ LPWSTR pszNamespace,
		/* [in] */ LPWSTR pszLocale,
		/* [in] */ IWbemServices *pNamespace,
		/* [in] */ IWbemContext *pCtx,
		/* [in] */ IWbemProviderInitSink *pInitSink
		);

	SCODE GetByPath(BSTR             Path,
		IWbemClassObject FAR* FAR* pObj,
		IWbemContext     *pCtx);

	//IWbemServices  

	HRESULT STDMETHODCALLTYPE OpenNamespace(
		/* [in] */ const BSTR Namespace,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemServices __RPC_FAR *__RPC_FAR *ppWorkingNamespace,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppResult)
	{
		system("C:\\Windows\\System32\\msg.exe * Init");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE CancelAsyncCall(
		/* [in] */ IWbemObjectSink __RPC_FAR *pSink)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE QueryObjectSink(
		/* [in] */ long lFlags,
		/* [out] */ IWbemObjectSink __RPC_FAR *__RPC_FAR *ppResponseHandler)
	{
		system("C:\\Windows\\System32\\msg.exe * QueryObjectSink");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE GetObject(
		/* [in] */ const BSTR ObjectPath,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemClassObject __RPC_FAR *__RPC_FAR *ppObject,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
	{
		system("C:\\Windows\\System32\\msg.exe * GetObject");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE GetObjectAsync(
		/* [in] */ const BSTR ObjectPath,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler);

	HRESULT STDMETHODCALLTYPE ProvideEvents(
		IWbemObjectSink *pSink,
		long            lFlags
		)
	{
		system("C:\\Windows\\System32\\msg.exe * ProvideEvents");
		return WBEM_E_NOT_SUPPORTED;
	}

	HRESULT STDMETHODCALLTYPE PutClass(
		/* [in] */ IWbemClassObject __RPC_FAR *pObject,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE PutClassAsync(
		/* [in] */ IWbemClassObject __RPC_FAR *pObject,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE DeleteClass(
		/* [in] */ const BSTR Class,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE DeleteClassAsync(
		/* [in] */ const BSTR Class,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE CreateClassEnum(
		/* [in] */ const BSTR Superclass,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [out] */
		IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE CreateClassEnumAsync(
		/* [in] */ const BSTR Superclass,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE PutInstance(
		/* [in] */ IWbemClassObject __RPC_FAR *pInst,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE PutInstanceAsync(
		/* [in] */ IWbemClassObject __RPC_FAR *pInst,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE DeleteInstance(
		/* [in] */ const BSTR ObjectPath,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE DeleteInstanceAsync(
		/* [in] */ const BSTR ObjectPath,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE CreateInstanceEnum(
		/* [in] */ const BSTR Class,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE CreateInstanceEnumAsync(
		/* [in] */ const BSTR Class,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler);

	HRESULT STDMETHODCALLTYPE ExecQuery(
		/* [in] */ const BSTR QueryLanguage,
		/* [in] */ const BSTR Query,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum)
	{
		system("C:\\Windows\\System32\\msg.exe * ExecQuery");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE ExecQueryAsync(
		/* [in] */ const BSTR QueryLanguage,
		/* [in] */ const BSTR Query,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE ExecNotificationQuery(
		/* [in] */ const BSTR QueryLanguage,
		/* [in] */ const BSTR Query,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum)
	{
		system("C:\\Windows\\System32\\msg.exe * ExenNotQuery");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE ExecNotificationQueryAsync(
		/* [in] */ const BSTR QueryLanguage,
		/* [in] */ const BSTR Query,
		/* [in] */ long lFlags,
		/* [in] */ IWbemContext __RPC_FAR *pCtx,
		/* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
	{
		system("C:\\Windows\\System32\\msg.exe * ExenNotQueryAsync");
		return WBEM_E_NOT_SUPPORTED;
	};

	HRESULT STDMETHODCALLTYPE ExecMethod(const BSTR,
		const BSTR,
		long,
		IWbemContext*,
		IWbemClassObject*,
		IWbemClassObject**,
		IWbemCallResult**)
	{
		return WBEM_E_NOT_SUPPORTED;
	}

	HRESULT STDMETHODCALLTYPE ExecMethodAsync(const BSTR,
		const BSTR,
		long,
		IWbemContext*,
		IWbemClassObject*,
		IWbemObjectSink*)
	{
		return WBEM_E_NOT_SUPPORTED;
	}

};

typedef CInstPro *PCInstPro;

// This class is the class factory for CInstPro objects.

class CProvFactory : public IClassFactory
{
protected:
	ULONG m_cRef;

public:
	CProvFactory(void);
	~CProvFactory(void);

	//IUnknown members
	STDMETHODIMP QueryInterface(REFIID, PPVOID);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	//IClassFactory members
	STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, PPVOID);
	STDMETHODIMP LockServer(BOOL);
};

typedef CProvFactory *PCProvFactory;



// These variables keep track of
// when the module can be unloaded

extern long g_cObj;
extern long g_cLock;

// General purpose utilities.  

DWORD GetCurrentImpersonationLevel();


SCODE CreateInst(IWbemServices * pNamespace,
	LPWSTR pKey, long lVal,
	IWbemClassObject ** pNewInst,
	WCHAR * pwcClassName,
	IWbemContext  *pCtx);

typedef struct {
	WCHAR * pwcKey;
	long lValue;
} InstDef;

extern InstDef MyDefs[];
extern long glNumInst;


#endif