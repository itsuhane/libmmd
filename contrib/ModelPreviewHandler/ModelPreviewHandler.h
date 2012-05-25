#pragma once

#include <windows.h>
#include <shlobj.h>
//#include <thumbcache.h>

class ModelPreviewHandler : 
    public IInitializeWithStream, 
    public IPreviewHandler, 
    public IPreviewHandlerVisuals, 
    public IOleWindow, 
    public IObjectWithSite
{
public:
    // IUnknown
    IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv);
    IFACEMETHODIMP_(ULONG) AddRef();
    IFACEMETHODIMP_(ULONG) Release();

    // IInitializeWithStream
    IFACEMETHODIMP Initialize(IStream *pStream, DWORD grfMode);

    // IPreviewHandler
    IFACEMETHODIMP SetWindow(HWND hwnd, const RECT *prc);
    IFACEMETHODIMP SetFocus();
    IFACEMETHODIMP QueryFocus(HWND *phwnd);
    IFACEMETHODIMP TranslateAccelerator(MSG *pmsg);
    IFACEMETHODIMP SetRect(const RECT *prc);
    IFACEMETHODIMP DoPreview();
    IFACEMETHODIMP Unload();

    // IPreviewHandlerVisuals (Optional)
    IFACEMETHODIMP SetBackgroundColor(COLORREF color);
    IFACEMETHODIMP SetFont(const LOGFONTW *plf);
    IFACEMETHODIMP SetTextColor(COLORREF color);

    // IOleWindow
    IFACEMETHODIMP GetWindow(HWND *phwnd);
    IFACEMETHODIMP ContextSensitiveHelp(BOOL fEnterMode);

    // IObjectWithSite
    IFACEMETHODIMP SetSite(IUnknown *punkSite);
    IFACEMETHODIMP GetSite(REFIID riid, void **ppv);

	ModelPreviewHandler();

protected:
    ~ModelPreviewHandler();

private:
    long m_cRef;
    IStream *m_pStream;
    HWND m_hwndParent;
    RECT m_rcParent;
    HWND m_hwndPreview;
    IUnknown *m_punkSite;

    HRESULT CreatePreviewWindow();

};
