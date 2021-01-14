#include <fstream>
#include <string>
#include <iostream>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <WinUser.h>
#include "UI.h"

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

class UI;

UI::UI() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pLightSlateGrayBrush(NULL),
	m_pCornflowerBlueBrush(NULL)
{
}

UI::~UI() {

	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pLightSlateGrayBrush);
	SafeRelease(&m_pCornflowerBlueBrush);
}


void Run() {

    MSG msg = { 0 };

    //loop until WM_QUIT
    //GetMessage puts application to sleep until message
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {

            //game/animation stuff
                //cpu.Step();
        }

    }

   
}


HRESULT UI::InitWindowsApp()
{
    HRESULT hr;

    hr = CreateDeviceIndependentResources();
    //first task to creating window is to describe characteristics using WNDCLASS structure
    if (SUCCEEDED(hr)) {
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = UI::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = L"BasicWndClass";

        //register this wndclass instance with windows
        //so that a window can be created

        RegisterClassEx(&wcex);

        //get system dpi
        UINT dpi = GetDpiForWindow(m_hwnd);


        //create window
        //this function returns a handle to the window
        //many WIN32 API functions dealing with windows
        //require an HWND to know what window to act on.

        m_hwnd = CreateWindow(L"BasicWndClass",
            L"Wnd32Basic",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpi / 96.f)),
            static_cast<UINT>(ceil(480.f * dpi / 96.f)),
            NULL,
            NULL,
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

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &m_pDirect2dFactory);

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
    }

    return hr;
}


void UI::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pCornflowerBlueBrush);
}













