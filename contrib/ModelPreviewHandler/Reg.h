#pragma once

#include <windows.h>

HRESULT RegisterInprocServer(PCWSTR pszModule, const CLSID& clsid, PCWSTR pszFriendlyName, PCWSTR pszThreadModel, const GUID& appId);
HRESULT UnregisterInprocServer(const CLSID& clsid, const GUID& appId);
HRESULT RegisterShellExtPreviewHandler(PCWSTR pszFileType, const CLSID& clsid, PCWSTR pszDescription);
HRESULT UnregisterShellExtPreviewHandler(PCWSTR pszFileType, const CLSID& clsid);