#include "Reg.h"
#include <strsafe.h>

#pragma region Registry Helper Functions
HRESULT SetHKCRRegistryKeyAndValue(PCWSTR pszSubKey, PCWSTR pszValueName, PCWSTR pszData, DWORD dwType = REG_SZ)
{
    HRESULT hr;
    HKEY hKey = NULL;

    hr = HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CLASSES_ROOT, pszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL));

    if (SUCCEEDED(hr))
    {
        if (pszData != NULL)
        {
            DWORD cbData = lstrlen(pszData) * sizeof(*pszData);
            hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, pszValueName, 0, dwType, reinterpret_cast<const BYTE *>(pszData), cbData));
        }

        RegCloseKey(hKey);
    }

    return hr;
}

HRESULT GetHKCRRegistryKeyAndValue(PCWSTR pszSubKey, PCWSTR pszValueName, PWSTR pszData, DWORD cbData)
{
    HRESULT hr;
    HKEY hKey = NULL;

    hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CLASSES_ROOT, pszSubKey, 0, KEY_READ, &hKey));

    if (SUCCEEDED(hr))
    {
        hr = HRESULT_FROM_WIN32(RegQueryValueEx(hKey, pszValueName, NULL, NULL, reinterpret_cast<LPBYTE>(pszData), &cbData));
        RegCloseKey(hKey);
    }

    return hr;
}

#pragma endregion

HRESULT RegisterInprocServer(PCWSTR pszModule, const CLSID& clsid, PCWSTR pszFriendlyName, PCWSTR pszThreadModel, const GUID& appId)
{
    if (pszModule == NULL || pszThreadModel == NULL)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;

    wchar_t szCLSID[MAX_PATH];
    StringFromGUID2(clsid, szCLSID, ARRAYSIZE(szCLSID));

    wchar_t szAppID[MAX_PATH];
    StringFromGUID2(appId, szAppID, ARRAYSIZE(szAppID));

    wchar_t szSubkey[MAX_PATH];

    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s", szCLSID);
    if (SUCCEEDED(hr))
    {
        hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszFriendlyName);

        if (SUCCEEDED(hr))
        {
            hr = SetHKCRRegistryKeyAndValue(szSubkey, L"AppID", szAppID);
        }

        if (SUCCEEDED(hr))
        {
            hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s\\InprocServer32", szCLSID);
            if (SUCCEEDED(hr))
            {
                hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, pszModule);
                if (SUCCEEDED(hr))
                {
                    hr = SetHKCRRegistryKeyAndValue(szSubkey, L"ThreadingModel", pszThreadModel);
                }
            }
        }
    }

    if (SUCCEEDED(hr))
    {
        hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"AppID\\%s", szAppID);
        if (SUCCEEDED(hr))
        {
            hr = SetHKCRRegistryKeyAndValue(szSubkey, L"DllSurrogate", L"%SystemRoot%\\system32\\prevhost.exe", REG_EXPAND_SZ);
        }
    }

    return hr;
}

HRESULT UnregisterInprocServer(const CLSID& clsid, const GUID& appId)
{
    HRESULT hr = S_OK;

    wchar_t szCLSID[MAX_PATH];
    StringFromGUID2(clsid, szCLSID, ARRAYSIZE(szCLSID));

    wchar_t szAppID[MAX_PATH];
    StringFromGUID2(appId, szAppID, ARRAYSIZE(szAppID));

    wchar_t szSubkey[MAX_PATH];

    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"CLSID\\%s", szCLSID);
    if (SUCCEEDED(hr))
    {
        hr = HRESULT_FROM_WIN32(RegDeleteTree(HKEY_CLASSES_ROOT, szSubkey));
    }

    if (SUCCEEDED(hr))
    {
        hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"AppID\\%s", szAppID);
        if (SUCCEEDED(hr))
        {
            hr = HRESULT_FROM_WIN32(RegDeleteTree(HKEY_CLASSES_ROOT, szSubkey));
        }
    }

    return hr;
}

HRESULT RegisterShellExtPreviewHandler(PCWSTR pszFileType, const CLSID& clsid, PCWSTR pszDescription)
{
    if (pszFileType == NULL)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;

    wchar_t szCLSID[MAX_PATH];
    StringFromGUID2(clsid, szCLSID, ARRAYSIZE(szCLSID));

    wchar_t szSubkey[MAX_PATH];

    if (*pszFileType == L'.')
    {
        wchar_t szDefaultVal[260];
        hr = GetHKCRRegistryKeyAndValue(pszFileType, NULL, szDefaultVal, sizeof(szDefaultVal));

        if (SUCCEEDED(hr) && szDefaultVal[0] != L'\0')
        {
            pszFileType = szDefaultVal;
        }
    }

    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"%s\\shellex\\{8895b1c6-b41f-4c1c-a562-0d564250836f}", pszFileType);
    if (SUCCEEDED(hr))
    {
        hr = SetHKCRRegistryKeyAndValue(szSubkey, NULL, szCLSID);
    }
    if (SUCCEEDED(hr))
    {
        HKEY hKey = NULL;
        hr = HRESULT_FROM_WIN32(RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\PreviewHandlers", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL));
        if (SUCCEEDED(hr))
        {
            DWORD cbData = (pszDescription == NULL) ? 0 : (lstrlen(pszDescription) * sizeof(*pszDescription));
            hr = HRESULT_FROM_WIN32(RegSetValueEx(hKey, szCLSID, 0, REG_SZ, reinterpret_cast<const BYTE *>(pszDescription), cbData));

            RegCloseKey(hKey);
        }
    }

    return hr;
}

HRESULT UnregisterShellExtPreviewHandler(PCWSTR pszFileType, const CLSID& clsid)
{
    if (pszFileType == NULL)
    {
        return E_INVALIDARG;
    }

    HRESULT hr;

    wchar_t szCLSID[MAX_PATH];
    StringFromGUID2(clsid, szCLSID, ARRAYSIZE(szCLSID));

    wchar_t szSubkey[MAX_PATH];

    if (*pszFileType == L'.')
    {
        wchar_t szDefaultVal[260];
        hr = GetHKCRRegistryKeyAndValue(pszFileType, NULL, szDefaultVal, sizeof(szDefaultVal));

        if (SUCCEEDED(hr) && szDefaultVal[0] != L'\0')
        {
            pszFileType = szDefaultVal;
        }
    }

    hr = StringCchPrintf(szSubkey, ARRAYSIZE(szSubkey), L"%s\\shellex\\{8895b1c6-b41f-4c1c-a562-0d564250836f}", pszFileType);
    if (SUCCEEDED(hr))
    {
        hr = HRESULT_FROM_WIN32(RegDeleteTree(HKEY_CLASSES_ROOT, szSubkey));
    }

    if (SUCCEEDED(hr))
    {
        HKEY hKey = NULL;

        hr = HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\PreviewHandlers", 0, KEY_WRITE, &hKey));
        if (SUCCEEDED(hr))
        {
            hr = HRESULT_FROM_WIN32(RegDeleteValue(hKey, szCLSID));
            if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                hr = S_OK;
            }

            RegCloseKey(hKey);
        }
        else if (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
        {
            hr = S_OK;
        }
    }

    return hr;
}
