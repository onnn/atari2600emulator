// Windows Header Files:
#include <windows.h>

// C RunTime Header Files:
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "UI.h"
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite")


template<class Interface>
inline void SafeRelease(
	Interface** ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define createWindowButtonInVideoWindow 101
#define createWindowButtonInMemoryViewerWindow 201


#define IDM_FILE_NEW 1
#define IDM_FILE_OPEN 2
#define IDM_FILE_QUIT 3
#define IDM_TOOLS_MEMORY_VIEWER 4

HWND UI::m_handleForMemoryViewerWindow;
HWND UI::m_hwnd;
WNDCLASSEX UI::memoryViewerWindowClass;
WNDCLASSEX UI::videoWindowClass;

class UI;

UI::UI() :
    //m_hwnd(NULL),
    m_pDirect2dFactory(NULL),
    m_pRenderTarget(NULL),
    m_pLightSlateGrayBrush(NULL),
    m_pCornflowerBlueBrush(NULL),
    videoWindowOpen(false),
    memoryViewerWindowOpen(false),
    videoWindowWindowClassCreated(false),
    memoryViewerWindowClassCreated(false)
{
}

UI::~UI() {

	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}


void UI::Run() {

    MSG msg = { 0 };

    //loop until WM_QUIT
    //GetMessage puts application to sleep until message
    while (msg.message != WM_QUIT) {

        while (GetMessage(&msg, NULL, 0, 0)) 
           {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }

   
}


HRESULT UI::InitWindowsApp()
{
    HRESULT hr;

    hr = CreateDeviceIndependentResources();
    //first task to creating window is to describe characteristics using WNDCLASS structure
    if (SUCCEEDED(hr)) {
        videoWindowClass = { sizeof(WNDCLASSEX) };
        memoryViewerWindowClass = { sizeof(WNDCLASSEX) };

        HDC screen = GetDC(0);
        auto dpiScaleX_ = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
        auto dpiScaleY_ = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
        ReleaseDC(0, screen);

        videoWindowClass.style = CS_HREDRAW | CS_VREDRAW;
        videoWindowClass.lpfnWndProc = UI::WndProc;
        videoWindowClass.hInstance = HINST_THISCOMPONENT;
        videoWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        videoWindowClass.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        videoWindowClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
        videoWindowClass.lpszClassName = L"Simple menu";

       
        //register this wndclass instance with windows
        //so that a window can be created

        RegisterClassEx(&videoWindowClass);
        RegisterClassEx(&memoryViewerWindowClass);

        //get system dpi
        //UINT dpi = GetDpiForWindow(m_hwnd);


        //create window
        //this function returns a handle to the window
        //many WIN32 API functions dealing with windows
        //require an HWND to know what window to act on.

        m_hwnd = CreateWindow(videoWindowClass.lpszClassName,
            L"Simple menu",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            100,
            100,
            350,
            250,
            0,
            0,
            HINST_THISCOMPONENT,
            this
        );

        hr = m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr)) {

            ShowWindow(m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(m_hwnd);
        }
  
          }
    return hr;
}

HRESULT UI::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    if (SUCCEEDED(hr))
    {

        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&pDWriteFactory_)
        );
        wszText_ = L"Hello World using DirectWrite!";
        cTextLength_ = (UINT32)wcslen(wszText_);
    }

    if (SUCCEEDED(hr))
    {
        hr = pDWriteFactory_->CreateTextFormat(
            L"Gabriola",
            NULL,
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            72.0f,
            L"en-us",
            &pTextFormat_
        );
    }
    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    return hr;
}

HRESULT UI::CreateDeviceResources()
{

    HRESULT hr = S_OK;

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
        );

        hr = m_pDirect2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            //create a gray brush
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &m_pLightSlateGrayBrush
            );
        }

        if (SUCCEEDED(hr))
        {
            //create a blue brush
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                &m_pCornflowerBlueBrush
            );
        }
        if (SUCCEEDED(hr))
        {
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &m_pBlackBrush
            );
        }
    }

    return hr;
}


void UI::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
    SafeRelease(&m_pBlackBrush);
}

LRESULT CALLBACK UI::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    
    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        UI* pUI = (UI*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pUI)
        );

        result = 1;
                        AddMenus(hwnd);
    }
    else
    {
        UI* pUI = reinterpret_cast<UI*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                m_hwnd,
                GWLP_USERDATA
            )));
 
        bool wasHandled = false;

        if (pUI)
        {

            switch (message)
            {


            case WM_COMMAND:

                switch (LOWORD(wParam)) {

                case IDM_FILE_NEW:
                case IDM_FILE_OPEN:

                    MessageBeep(MB_ICONINFORMATION);
                    break;

                case IDM_TOOLS_MEMORY_VIEWER:

                    createMemoryViewerWindow(memoryViewerWindowClass, m_handleForMemoryViewerWindow, HINST_THISCOMPONENT, SW_NORMAL);
                    break;

                case IDM_FILE_QUIT:

                    SendMessage(m_hwnd, WM_CLOSE, 0, 0);
                    break;
                }

                break;
            case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                pUI->OnResize(width, height);
            }

            result = 0;
            wasHandled = true;
            break;

            case WM_DISPLAYCHANGE:
            {
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_PAINT:
            {
                pUI->OnRender();
                ValidateRect(hwnd, NULL);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            result = 1;
            wasHandled = true;
            break;

            }

        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }

    }

    return result;
}

LRESULT CALLBACK UI::WndProcForMemoryViewer(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    UI* pUI{};
        switch (message)
        {

        case WM_SIZE:
        {
            UINT width = LOWORD(lParam);
            UINT height = HIWORD(lParam);
            pUI->OnResize(width, height);
        }

               break;

        case WM_DISPLAYCHANGE:
        {
            InvalidateRect(hwnd, NULL, FALSE);
        }
        result = 0;
        break;

        case WM_PAINT:
        {
            pUI->OnRender();
            ValidateRect(hwnd, NULL);
        }
        result = 0;
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        result = 1;
        break;

        



    }
    return result;
}

HRESULT UI::OnRender()
{

    HRESULT hr = S_OK;

    hr = CreateDeviceResources();

    if (SUCCEEDED(hr))
    {

        m_pRenderTarget->BeginDraw();
        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();

    int width = static_cast<int>(rtSize.width);
    int height = static_cast<int>(rtSize.height);

    for (int x = 0; x < width; x += 10)
    {
        m_pRenderTarget->DrawLine(D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
            D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    for (int y = 0; y < height; y += 10)
    {
        m_pRenderTarget->DrawLine(
            D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
            D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
            m_pLightSlateGrayBrush,
            0.5f
        );
    }

    D2D1_RECT_F rectangle1 = D2D1::RectF(
        0,
        0,
        rtSize.width,
        rtSize.height
    );

       // Draw a filled rectangle.
    m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);
    // Draw the outline of a rectangle.
    //m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

    m_pRenderTarget->DrawTextW(wszText_,
        cTextLength_,
        pTextFormat_,
        rectangle1,
        m_pBlackBrush);

    hr = m_pRenderTarget->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }

    return hr;
}

void UI::OnResize(UINT width, UINT height)
{
    if (m_pRenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}

void UI::AddMenus(HWND hwnd) {

    HMENU hMenubar;
    HMENU hFileMenu;
    HMENU hToolsMenu;

    hMenubar = CreateMenu();
    hFileMenu = CreateMenu();
    hToolsMenu = CreateMenu();

    AppendMenuW(hFileMenu, MF_STRING, 1, L"&Open");
    AppendMenuW(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hFileMenu, MF_STRING, 3, L"&Quit");
    AppendMenuW(hToolsMenu, MF_STRING, IDM_TOOLS_MEMORY_VIEWER, L"&Memory Viewer");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hToolsMenu, L"&Tools");
    SetMenu(hwnd, hMenubar);

}

void UI::createMemoryViewerWindow(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd) {

    HRESULT hr;
    HDC screen = GetDC(0);
    auto dpiScaleX_ = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
    auto dpiScaleY_ = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
    ReleaseDC(0, screen);

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProcForMemoryViewer;
    wc.hInstance = HINST_THISCOMPONENT;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszClassName = L"Simple menu";
    wc.lpszMenuName = NULL;

    hwnd = CreateWindowEx(NULL, wc.lpszClassName, L"Window 2", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 200, 170, 640, 480, m_hwnd, NULL, HINST_THISCOMPONENT, NULL);
    SetMenu(hwnd, NULL);

    hr = hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr)) {

        ShowWindow(hwnd, nShowCmd);
        UpdateWindow(hwnd);
    }

}
