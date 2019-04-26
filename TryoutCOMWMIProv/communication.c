#include "communication.h"

void SendRequest(LPSTR *totalBuffer) {
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	BOOL  bResults = FALSE;
	LPSTR pszOutBuffer;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	// Error string for error codes
	char *errStr = malloc(sizeof(char) * 10);

	// Initialize total buffer.
	*totalBuffer = "";

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, L"127.0.0.1",
			4443, 0);

	// Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_SECURE);

	// Send a request.
	if (hRequest) {
		int retry, result;
		do
		{
			retry = 0;
			result = NO_ERROR;
			bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
			// no retry on success, possible retry on failure
			if (bResults == FALSE)
			{
				result = GetLastError();

				if (result == ERROR_WINHTTP_SECURE_FAILURE)
				{
					DWORD dwFlags =
						SECURITY_FLAG_IGNORE_UNKNOWN_CA |
						SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE |
						SECURITY_FLAG_IGNORE_CERT_CN_INVALID |
						SECURITY_FLAG_IGNORE_CERT_DATE_INVALID;

					if (WinHttpSetOption(
						hRequest,
						WINHTTP_OPTION_SECURITY_FLAGS,
						&dwFlags,
						sizeof(dwFlags)))
					{
						retry = 1;
					}
				}
				
				else if (result == ERROR_WINHTTP_RESEND_REQUEST)
				{
					retry = 1;
				}
			}
		} while (retry);
	}

	// End the request.
	if (bResults) {
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	// Keep checking for data until there is nothing left.
	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				sprintf_s(errStr, 10, "%d", GetLastError());
				system(strConcat("C:\\Windows\\System32\\msg.exe * QueryDataAvailable - ", errStr));
			}
			// Allocate space for the buffer.
			pszOutBuffer = (char*) malloc( dwSize + 1 );
			if (!pszOutBuffer) {
				dwSize = 0;
			} else {
				// Initialize buffer (null-terminated string)
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
					system("C:\\Windows\\System32\\msg.exe * ErrorWinHttpReadData");
				} else {
					// strConcat creates new buffer.
					*totalBuffer = strConcat((char*)*totalBuffer, (char*)pszOutBuffer);
				}
			}
		} while (dwSize > 0);
	}
	
	// Report any errors.
	if (!bResults) {
		sprintf_s(errStr, 10, "%d", GetLastError());
		system(strConcat("C:\\Windows\\System32\\msg.exe * CommbResults - ", errStr));
	}
	
	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
}