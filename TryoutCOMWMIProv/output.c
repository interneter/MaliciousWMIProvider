#include "output.h"

/**
	Creates file containing specific data.

	@param path - File path to be created.
	@param data - Data to write in the file.
	@return Nothing.
*/
static void writeFilePath(char *path, char *data)
{
	FILE *fp;

	fopen_s(&fp, path, "wb");
	fprintf(fp, data);
	fclose(fp);
}

/**
	The fucntion checks if the given string is a valid path.

	@param path - File path to be created.
	@return 0 if the path is invalid. Else, the function returns 1.
*/
static int validateFilePathString(char *path)
{
	// Basic input sanity check.
	if ( path == NULL || !strcmp("", path) )
		return 0;
	return 1;
}

/**
	Creates file containing specific data.
	If path is invalid, default path will be created.

	@param path - File path to be created.
	@param data - Data to write in the file.
	@return 0 if the function failed. Else, any number can be returned.
*/
int writeOutputToFile(char *path, char *data)
{
	// If path is valid, create it. Else, create the file with the default path. 
	validateFilePathString(path) ? writeFilePath(path, data) : writeFilePath(DEFAULT_OUTPUT_FILE_PATH, data);
	return 0;
}

static int validateRegistryPath(TCHAR *path)
{
	if (path == NULL || !_tcsncmp(_T(""), path, tcharLength(path) ))
		return 1;
	return 0;
}

static HKEY parseRegRoot(TCHAR *base)
{
	TCHAR *lowercase_base = tcharLower(base);
	int base_len = tcharLength(base);

	if (base == NULL || !_tcsncmp(_T(""), base, base_len))
		return 0;

	if (!_tcsncmp(_T("hklm"), lowercase_base, base_len) || !_tcsncmp(_T("hkey_local_machine"), lowercase_base, base_len))
		return HKEY_LOCAL_MACHINE;
	else if (!_tcsncmp(_T("hkcr"), lowercase_base, base_len) || !_tcsncmp(_T("hkey_classes_root"), lowercase_base, base_len))
		return HKEY_CLASSES_ROOT;
	else if (!_tcsncmp(_T("hkcc"), lowercase_base, base_len) || !_tcsncmp(_T("hkey_current_config"), lowercase_base, base_len))
		return HKEY_CURRENT_CONFIG;
	else if (!_tcsncmp(_T("hkcu"), lowercase_base, base_len) || !_tcsncmp(_T("hkey_current_user"), lowercase_base, base_len))
		return HKEY_CURRENT_USER;
	else if (!_tcsncmp(_T("hku"), lowercase_base, base_len) || !_tcsncmp(_T("hkey_users"), lowercase_base, base_len))
		return HKEY_USERS;
	else
		return 0;
}

/**
	Writes GenericValue to registry.

	@param path - Relative path to the registry tree to create the given key name.
	@param key - Key name to create.
	@param data - Data to write in the registry key.
	@return 0 if the function failed. Else, any number presens an error might be returned.
*/

int writeToRegistry(TCHAR *base, TCHAR *path, TCHAR *key, GenericValue data)
{
	HKEY returnRegHandle;
	int return_value = 0;
	HKEY base_root;

	base_root = parseRegRoot(base);

	if (base_root == 0)
		return INVALID_REG_BASE;

	return_value = validateRegistryPath(path);
	if (return_value)
		return INVALID_REGISTRY_PATH;

	return_value = RegCreateKeyEx(base_root, path, 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &returnRegHandle, NULL);
	if (return_value != 0)
		// "If the function fails, the return value is a nonzero error code defined in Winerror.h", dammit.
		// Which errors RegCreateKeyEx might return?!?!?! (defined in winerror.h, of course...)
		return return_value;

	char *buf;

	switch (data.type)
	{
	case GENERIC_INTEGER:
		buf = malloc(10);
		_itoa_s(data.value.integer, buf, 10, 10);
		RegSetValueEx(returnRegHandle, key, 0, REG_DWORD, (BYTE*)buf, sizeof(data.value.integer));
		break;
	case GENERIC_STRING:
		RegSetValueEx(returnRegHandle, key, 0, REG_SZ, (BYTE*)data.value.string, (DWORD)strlen(data.value.string));
		break;
	case GENERIC_REAL:
		RegSetValueEx(returnRegHandle, key, 0, REG_SZ, (BYTE*)genericValueToString(data), (DWORD) strlen(data.value.string));
		break;
	case GENERIC_POINTER:
		RegSetValueEx(returnRegHandle, key, 0, REG_SZ, (BYTE*)genericValueToString(data), (DWORD) strlen(data.value.string));
		break;
	case GENERIC_TSTRING:
		RegSetValueEx(returnRegHandle, key, 0, REG_SZ, (BYTE*)data.value.tstring, tcharLength(data.value.tstring));
		break;
	case GENERIC_WSTRING:
		RegSetValueEx(returnRegHandle, key, 0, REG_SZ, (BYTE*)data.value.wstring, (DWORD) wcslen(data.value.wstring));
		break;
	default:
		return UNKNOWN_GENERIC_STRING_TYPE;
		break;
	}
	return NORMAL_RETURN_VALUE;
}

GenericValue output(GenericValue data, char *properties, int method)
{
	GenericValue out;

	if (method == WRITE_TO_FILE)
	{
		out.type = GENERIC_INTEGER;
		out.value.integer = writeOutputToFile(properties, genericValueToString(data) );
	}
	else if (method == BASIC_RETURN)
	{
		return data;
	}
	else if (method == WRITE_TO_REGISTRY)
	{
		out.type = GENERIC_INTEGER;
		out.value.integer = writeToRegistry(_T(DEFAULT_OUTPUT_REG_BASE), _T(DEFAULT_OUTPUT_REG_PATH), _T(DEFAULT_OUTPUT_REG_KEY), data);
	}
	else
	{
		out.type = GENERIC_INTEGER;
		out.value.integer = 0;
	}
	return out;
}