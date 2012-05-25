// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <guiddef.h>
#include "ClassFactory.h"
#include "Reg.h"

// {5FF07F9E-3D42-4C18-BEA9-E0921E042A77}
static const CLSID CLSID_ModelPreviewHandler = 
{ 0x5ff07f9e, 0x3d42, 0x4c18, { 0xbe, 0xa9, 0xe0, 0x92, 0x1e, 0x4, 0x2a, 0x77 } };

// {146D77FE-9C92-4322-A687-31DA6FC58664}
static const GUID APPID_ModelPreviewHandler = 
{ 0x146d77fe, 0x9c92, 0x4322, { 0xa6, 0x87, 0x31, 0xda, 0x6f, 0xc5, 0x86, 0x64 } };

HINSTANCE g_hInst = NULL;
long g_cDllRef = 0;

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
        g_hInst = hModule;
        DisableThreadLibraryCalls(hModule);
        break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
    HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;

    if (IsEqualCLSID(CLSID_ModelPreviewHandler, rclsid))
    {
        hr = E_OUTOFMEMORY;

        ClassFactory *pClassFactory = new ClassFactory();
        if (pClassFactory)
        {
            hr = pClassFactory->QueryInterface(riid, ppv);
            pClassFactory->Release();
        }
    }

    return hr;
}

STDAPI DllCanUnloadNow(void)
{
    return g_cDllRef > 0 ? S_FALSE : S_OK;
}

STDAPI DllRegisterServer(void)
{
    HRESULT hr;

    wchar_t szModule[MAX_PATH];
    if (GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule)) == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return hr;
    }

    hr = RegisterInprocServer(szModule, CLSID_ModelPreviewHandler, L"MikuMikuDance Model Preview Handler", L"Apartment", APPID_ModelPreviewHandler);
    if (SUCCEEDED(hr))
    {
        hr = RegisterShellExtPreviewHandler(L".pmd", CLSID_ModelPreviewHandler, L"PMDPreviewHandler");
        if (SUCCEEDED(hr))
        {
            hr = RegisterShellExtPreviewHandler(L".pmx", CLSID_ModelPreviewHandler, L"PMXPreviewHandler");
        }        
    }

    return hr;
}

STDAPI DllUnregisterServer(void)
{
    HRESULT hr = S_OK;

    wchar_t szModule[MAX_PATH];
    if (GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule)) == 0)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return hr;
    }

    hr = UnregisterInprocServer(CLSID_ModelPreviewHandler, APPID_ModelPreviewHandler);
    if (SUCCEEDED(hr))
    {
        hr = UnregisterShellExtPreviewHandler(L".pmd", CLSID_ModelPreviewHandler);
        if (SUCCEEDED(hr))
        {
            hr = UnregisterShellExtPreviewHandler(L".pmx", CLSID_ModelPreviewHandler);
        }
    }

    return hr;
}
