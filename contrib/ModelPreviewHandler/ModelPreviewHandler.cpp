// ModelPreviewHandler.cpp : Defines the exported functions for the DLL application.
//

#include "ModelPreviewHandler.h"
#include <Shlwapi.h>
#include <assert.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "resource.h"

#include <mmd/mmd.hxx>

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HINSTANCE   g_hInst;
extern long g_cDllRef;

mmd::Model* model = NULL;
std::wstring model_info_str1;
std::wstring model_info_str2;
std::wstring model_info_str3;

std::wstring* model_info[3] = {&model_info_str1, &model_info_str2, &model_info_str3};

static COLORREF g_bgColor = 0x00000000;
static COLORREF g_fgColor = 0x0000ffff;
static LOGFONTW g_sysFont;

static int mode = 0;

VOID Cleanup();

inline int RECTWIDTH(const RECT &rc)
{
    return (rc.right - rc.left);
}

inline int RECTHEIGHT(const RECT &rc)
{
    return (rc.bottom - rc.top);
}

// This is the constructor of a class that has been exported.
// see ModelPreviewHandler.h for the class definition
ModelPreviewHandler::ModelPreviewHandler() : m_cRef(1), m_pStream(NULL), m_hwndParent(NULL), m_hwndPreview(NULL), m_punkSite(NULL)
{
    InterlockedIncrement(&g_cDllRef);
}

ModelPreviewHandler::~ModelPreviewHandler()
{
    if (m_pStream)
    {
        m_pStream->Release();
        m_pStream = NULL;
    }

    if(model)
    {
        delete model;
        model = NULL;
    }

    InterlockedDecrement(&g_cDllRef);
}

#pragma region IUnknown

// Query to the interface the component supported.
IFACEMETHODIMP ModelPreviewHandler::QueryInterface(REFIID riid, void **ppv)
{
    static const QITAB qit[] = 
    {
        QITABENT(ModelPreviewHandler, IPreviewHandler),
        QITABENT(ModelPreviewHandler, IInitializeWithStream), 
        QITABENT(ModelPreviewHandler, IPreviewHandlerVisuals), 
        QITABENT(ModelPreviewHandler, IOleWindow), 
        QITABENT(ModelPreviewHandler, IObjectWithSite), 
        { 0 },
    };
    return QISearch(this, qit, riid, ppv);
}

// Increase the reference count for an interface on an object.
IFACEMETHODIMP_(ULONG) ModelPreviewHandler::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}

// Decrease the reference count for an interface on an object.
IFACEMETHODIMP_(ULONG) ModelPreviewHandler::Release()
{
    ULONG cRef = InterlockedDecrement(&m_cRef);
    if (0 == cRef)
    {
        delete this;
    }

    return cRef;
}

#pragma endregion

#pragma region IInitializeWithStream

// Initializes the preview handler with a stream. 
// Store the IStream and mode parameters so that you can read the item's data 
// when you are ready to preview the item. Do not load the data in Initialize. 
// Load the data in IPreviewHandler::DoPreview just before you render.
IFACEMETHODIMP ModelPreviewHandler::Initialize(IStream *pStream, DWORD grfMode)
{
    HRESULT hr = E_INVALIDARG;
    if (pStream)
    {
        // Initialize can be called more than once, so release existing valid 
        // m_pStream.
        if (m_pStream)
        {
            m_pStream->Release();
            m_pStream = NULL;
        }

        m_pStream = pStream;
        m_pStream->AddRef();
        hr = S_OK;
    }
    return hr;
}

#pragma endregion

#pragma region IPreviewHandler

// This method gets called when the previewer gets created. It sets the parent 
// window of the previewer window, as well as the area within the parent to be 
// used for the previewer window.
IFACEMETHODIMP ModelPreviewHandler::SetWindow(HWND hwnd, const RECT *prc)
{
    if (hwnd && prc)
    {
        m_hwndParent = hwnd;  // Cache the HWND for later use
        m_rcParent = *prc;    // Cache the RECT for later use

        if (m_hwndPreview)
        {
            // Update preview window parent and rect information
            SetParent(m_hwndPreview, m_hwndParent);
            SetWindowPos(m_hwndPreview, NULL, m_rcParent.left, m_rcParent.top, 
                RECTWIDTH(m_rcParent), RECTHEIGHT(m_rcParent), 
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
    return S_OK;
}

// Directs the preview handler to set focus to itself.
IFACEMETHODIMP ModelPreviewHandler::SetFocus()
{
    HRESULT hr = S_FALSE;
    if (m_hwndPreview)
    {
        ::SetFocus(m_hwndPreview);
        hr = S_OK;
    }
    return hr;
}

// Directs the preview handler to return the HWND from calling the GetFocus 
// function.
IFACEMETHODIMP ModelPreviewHandler::QueryFocus(HWND *phwnd)
{
    HRESULT hr = E_INVALIDARG;
    if (phwnd)
    {
        *phwnd = ::GetFocus();
        if (*phwnd)
        {
            hr = S_OK;
        }
        else
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }
    }
    return hr;
}

// Directs the preview handler to handle a keystroke passed up from the 
// message pump of the process in which the preview handler is running.
HRESULT ModelPreviewHandler::TranslateAccelerator(MSG *pmsg)
{
    HRESULT hr = S_FALSE;
    IPreviewHandlerFrame *pFrame = NULL;
    if (m_punkSite && SUCCEEDED(m_punkSite->QueryInterface(&pFrame)))
    {
        // If your previewer has multiple tab stops, you will need to do 
        // appropriate first/last child checking. This sample previewer has 
        // no tabstops, so we want to just forward this message out.
        hr = pFrame->TranslateAccelerator(pmsg);

        pFrame->Release();
    }
    return hr;
}

// This method gets called when the size of the previewer window changes 
// (user resizes the Reading Pane). It directs the preview handler to change 
// the area within the parent hwnd that it draws into.
IFACEMETHODIMP ModelPreviewHandler::SetRect(const RECT *prc)
{
    HRESULT hr = E_INVALIDARG;
    if (prc != NULL)
    {
        m_rcParent = *prc;
        if (m_hwndPreview)
        {
            // Preview window is already created, so set its size and position.
            SetWindowPos(m_hwndPreview, NULL, m_rcParent.left, m_rcParent.top,
                (m_rcParent.right - m_rcParent.left), // Width
                (m_rcParent.bottom - m_rcParent.top), // Height
                SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        }
        hr = S_OK;
    }
    return hr;
}

// The method directs the preview handler to load data from the source 
// specified in an earlier Initialize method call, and to begin rendering to 
// the previewer window.
IFACEMETHODIMP ModelPreviewHandler::DoPreview()
{
    // Cannot call more than once.
    // (Unload should be called before another DoPreview)
    if (m_hwndPreview != NULL || !m_pStream || model != NULL) 
    {
        return E_FAIL;
    }

    LARGE_INTEGER zero = {0};
    ULARGE_INTEGER end_ptr;
    m_pStream->Seek(zero, STREAM_SEEK_END, &end_ptr);
    m_pStream->Seek(zero, STREAM_SEEK_SET, NULL);

    try {
        mmd::FileReader file;
        mmd::buffer_type& buffer = file.GetBuffer();
        ULONG len = (ULONG)end_ptr.QuadPart;
        buffer.insert(buffer.end(), (size_t)len, 0);
        m_pStream->Read(&buffer[0], len, NULL);
        file.Reset();
        model = mmd::ReadModel(file);
    } catch(...) {
        return E_FAIL;
    }

    model_info_str1 = model->GetName();

    model_info_str2 = model->GetName()+L"\n\n"+model->GetDescription();

    model_info_str3 = model->GetName()+L"\n\n"+model->GetDescription();
    if((*model_info_str3.rbegin())==L'\n') {
        model_info_str3 = model_info_str3+L"\n";
    } else {
        model_info_str3 = model_info_str3+L"\n\n";
    }
    wchar_t buffer[64];
    wnsprintf(buffer, 60, L"%ld\n", model->GetVertexNum());
    model_info_str3 = model_info_str3+L"V: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetTriangleNum());
    model_info_str3 = model_info_str3+L"T: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetPartNum());
    model_info_str3 = model_info_str3+L"P: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetBoneNum());
    model_info_str3 = model_info_str3+L"B: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetMorphNum());
    model_info_str3 = model_info_str3+L"M: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetRigidBodyNum());
    model_info_str3 = model_info_str3+L"R: "+buffer;
    wnsprintf(buffer, 60, L"%ld\n", model->GetConstraintNum());
    model_info_str3 = model_info_str3+L"J: "+buffer;

    return CreatePreviewWindow();
}

// This method gets called when a shell item is de-selected. It directs the 
// preview handler to cease rendering a preview and to release all resources 
// that have been allocated based on the item passed in during the 
// initialization.
HRESULT ModelPreviewHandler::Unload()
{
    if (m_pStream)
    {
        m_pStream->Release();
        m_pStream = NULL;
    }

    if(model)
    {
        delete model;
        model = NULL;
    }

    if (m_hwndPreview)
    {
        Cleanup();
        DestroyWindow(m_hwndPreview);
        m_hwndPreview = NULL;
    }

    return S_OK;
}

#pragma endregion

#pragma region IPreviewHandlerVisuals (Optional)

// Sets the background color of the preview handler.
IFACEMETHODIMP ModelPreviewHandler::SetBackgroundColor(COLORREF color)
{
    //g_bgColor = color;
    return S_OK;
}

// Sets the font attributes to be used for text within the preview handler.
IFACEMETHODIMP ModelPreviewHandler::SetFont(const LOGFONTW *plf)
{
    g_sysFont = *plf;
    return S_OK;
}

// Sets the color of the text within the preview handler.
IFACEMETHODIMP ModelPreviewHandler::SetTextColor(COLORREF color)
{
    //g_fgColor = color;
    return S_OK;
}

#pragma endregion

#pragma region IOleWindow

// Retrieves a handle to one of the windows participating in in-place 
// activation (frame, document, parent, or in-place object window).
IFACEMETHODIMP ModelPreviewHandler::GetWindow(HWND *phwnd)
{
    HRESULT hr = E_INVALIDARG;
    if (phwnd)
    {
        *phwnd = m_hwndParent;
        hr = S_OK;
    }
    return hr;
}

// Determines whether context-sensitive help mode should be entered during an 
// in-place activation session
IFACEMETHODIMP ModelPreviewHandler::ContextSensitiveHelp(BOOL fEnterMode)
{
    return E_NOTIMPL;
}

#pragma endregion

#pragma region IObjectWithSite

// Provides the site's IUnknown pointer to the object.
IFACEMETHODIMP ModelPreviewHandler::SetSite(IUnknown *punkSite)
{
    if (m_punkSite)
    {
        m_punkSite->Release();
        m_punkSite = NULL;
    }
    return punkSite ? punkSite->QueryInterface(&m_punkSite) : S_OK;
}

// Gets the last site set with IObjectWithSite::SetSite. If there is no known 
// site, the object returns a failure code.
IFACEMETHODIMP ModelPreviewHandler::GetSite(REFIID riid, void **ppv)
{
    *ppv = NULL;
    return m_punkSite ? m_punkSite->QueryInterface(riid, ppv) : E_FAIL;
}

#pragma endregion

#pragma region Helper Functions

INT_PTR CALLBACK DialogProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

HRESULT ModelPreviewHandler::CreatePreviewWindow()
{
    assert(m_hwndPreview == NULL);
    assert(m_hwndParent != NULL);

    HRESULT hr = S_OK;

    m_hwndPreview = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DXDIALOG), 
        m_hwndParent, DialogProc);
    if (m_hwndPreview == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (SUCCEEDED(hr))
    {
        // Set the preview window position.
        SetWindowPos(m_hwndPreview, NULL, m_rcParent.left, m_rcParent.top,
            RECTWIDTH(m_rcParent), RECTHEIGHT(m_rcParent), 
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

        ShowWindow(m_hwndPreview, SW_SHOW);
    }

    return hr;
}

D3DPRESENT_PARAMETERS g_d3dpp;

LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device
ID3DXFont*          g_pInfoFont = NULL;

LPD3DXMESH        g_pMesh      = NULL;

float g_fDistance = 4.0f;
float g_fSpinX    = 0.0f;
float g_fSpinY    = 0.0f;

bool multisampling = false;

struct VERTEX
{
    float x, y, z;
    DWORD color;

    enum FVF
    {
        FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE 
    };
};

HRESULT validate_data()
{
    if( FAILED(D3DXCreateFont( g_pd3dDevice, g_sysFont.lfHeight, 0, g_sysFont.lfWeight, 1, FALSE, g_sysFont.lfCharSet,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        g_sysFont.lfFaceName, &g_pInfoFont ) ) )
    {
        return E_FAIL;
    }

    if( FAILED( D3DXCreateMeshFVF( (DWORD)model->GetTriangleNum(),
        (DWORD)model->GetVertexNum(),
        D3DXMESH_32BIT|D3DXMESH_MANAGED, VERTEX::FVF_Flags, 
        g_pd3dDevice, &g_pMesh ) ) )
    {
        return E_FAIL;
    }


    VERTEX* pVertices = NULL;

    if(SUCCEEDED(g_pMesh->LockVertexBuffer( 0, (void**)&pVertices ))) {

        for(size_t i=0;i<model->GetVertexNum();++i) {
            const mmd::Vector3f& coord = model->GetVertex(i).GetCoordinate();
            pVertices[i].x = coord.p.x;
            pVertices[i].y = coord.p.y;
            pVertices[i].z = coord.p.z;
            pVertices[i].color = 0xFFFFFFFF;
        }

        g_pMesh->UnlockVertexBuffer();
    }

    DWORD* pIndices = NULL;

    if(SUCCEEDED(g_pMesh->LockIndexBuffer( 0, (void**)&pIndices )))
    {
        for(size_t i=0, c=0;i<model->GetTriangleNum();++i) {
            for(size_t j=0;j<3;++j,++c) {
                pIndices[c] = model->GetTriangle(i).v[j];
            }
        }
        g_pMesh->UnlockIndexBuffer();
    }

    return S_OK;
}

VOID invalidate_data()
{
    if(g_pMesh != NULL)
    {
        g_pMesh->Release();
        g_pMesh = NULL;
    }

    if( g_pInfoFont != NULL )
    {
        g_pInfoFont->Release();
        g_pInfoFont = NULL;
    }
}

HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    D3DDISPLAYMODE d3ddm;

    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    ZeroMemory( &g_d3dpp, sizeof( g_d3dpp ) );
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = d3ddm.Format;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &g_d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 
        640.0f / 480.0f, 0.1f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,  TRUE ); 
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    mode = 0;

    return validate_data();
}

VOID Cleanup()
{
    invalidate_data();

    if( g_pd3dDevice != NULL )
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = NULL;
    }

    if( g_pD3D != NULL )
    {
        g_pD3D->Release();
        g_pd3dDevice = NULL;
    }
}

VOID Render()
{
    if( NULL == g_pd3dDevice )
        return;

    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( g_bgColor&0xFF, (g_bgColor>>8)&0xFF, (g_bgColor>>16)&0xFF ), 1.0f, 0 );

    D3DXMATRIX matPreTrans;
    D3DXMATRIX matPostTrans;
    D3DXMATRIX matScale;
    D3DXMATRIX matRotX;
    D3DXMATRIX matRotY;
    D3DXMATRIX matWorld;

    D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);

    D3DXMatrixRotationY(&matRotY, D3DXToRadian(g_fSpinX));
    D3DXMatrixRotationX(&matRotX, D3DXToRadian(g_fSpinY));

    D3DXMatrixTranslation( &matPreTrans, 0.0f, -0.5f, g_fDistance );
    D3DXMatrixTranslation( &matPostTrans, 0.0f, -0.5f, 0.0f );

    matWorld = matScale * matPostTrans * matRotY * matRotX * matPreTrans;
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        g_pMesh->DrawSubset(0);

        RECT rc;
        std::wstring message;
        ::SetRect(&rc, 5, 2, 0, 0);

        g_pInfoFont->DrawTextW(NULL, model_info[mode]->c_str(), -1, &rc, DT_NOCLIP, D3DCOLOR_XRGB( g_fgColor&0xFF, (g_fgColor>>8)&0xFF, (g_fgColor>>16)&0xFF ));
        g_pd3dDevice->EndScene();
    }

    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{
    static POINT ptLastMousePosit;
    static POINT ptCurrentMousePosit;
    static bool bMousing;

    switch (message) 
    { 
        case WM_DESTROY:
            Cleanup();
            return TRUE;
        case WM_INITDIALOG:
            InitD3D(hwndDlg);
            return TRUE;
        case WM_MOUSEMOVE:
            ptCurrentMousePosit.x = LOWORD (lParam);
            ptCurrentMousePosit.y = HIWORD (lParam);

            if( bMousing )
            {
                g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
                g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
                if(g_fSpinY>90) g_fSpinY=90;
                if(g_fSpinY<-90) g_fSpinY=-90;
                Render();
                ValidateRect( hwndDlg, NULL );
            }

            ptLastMousePosit.x = ptCurrentMousePosit.x;
            ptLastMousePosit.y = ptCurrentMousePosit.y;
            return TRUE;
        case WM_LBUTTONDOWN:
            ptLastMousePosit.x = ptCurrentMousePosit.x = LOWORD (lParam);
            ptLastMousePosit.y = ptCurrentMousePosit.y = HIWORD (lParam);
            bMousing = true;
            return TRUE;
        case WM_LBUTTONUP:
            bMousing = false;
            return TRUE;
        case WM_LBUTTONDBLCLK:
            mode = (mode+1)%3;
            Render();
            ValidateRect( hwndDlg, NULL );
            return TRUE;
        case WM_RBUTTONDOWN:
            return TRUE;
        case WM_RBUTTONUP:
            return TRUE;
        case WM_RBUTTONDBLCLK:
            return TRUE;
        case WM_SIZE:
            invalidate_data();
            if( g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED )
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                g_d3dpp.BackBufferWidth  = width;
                g_d3dpp.BackBufferHeight = height;

                HRESULT hr = g_pd3dDevice->Reset( &g_d3dpp );

                if( hr == D3DERR_INVALIDCALL )
                {
                    return FALSE;
                }

                D3DXMATRIX matProj;
                if(width<height) {
                    D3DXMatrixPerspectiveFovLH( &matProj, atan((float)height/(float)width), (float)width / height, 0.1f, 100.0f );
                } else {
                    D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), (float)width / height, 0.1f, 100.0f );
                }
                g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
                g_pd3dDevice->SetRenderState(D3DRS_ZENABLE,  TRUE ); 
                g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
                g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
            }
            if(FAILED(validate_data())) {
                return FALSE;
            }
            return TRUE;
        case WM_PAINT:
            Render();
            ValidateRect( hwndDlg, NULL );
            return TRUE;
        default:
            return FALSE; 
    } 
} 

#pragma endregion
