#include <iostream>
#include <windows.h>
#include "CPU.h"
#include "MEM.h"
#include "UI.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum class input {
     KEY_PRESS_SURFACE_DEFAULT,
     KEY_PRESS_SURFACE_UP,
     KEY_PRESS_SURFACE_DOWN,
     KEY_PRESS_SURFACE_LEFT,
     KEY_PRESS_SURFACE_RIGHT,
     KEY_PRESS_SURFACE_TOTAL


};

//Must include command line parameters for main to be recognized by SDL

    //Main window handle; used to identify a created window.
    HWND ghMainWnd = 0;
    MEM mem;
    CPU cpu;
    //wraps the code necessary to init a windows application.
    bool InitWindowsApp(HINSTANCE instanceHandle, int show);

    int Run(); //wraps the message loop code

    //The Window procedure handles events our window receives

    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    //Window equivalant to main()
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd)
    {

        mem.AllocateMemory("b.a26");
        cpu.Init();
        //first call our wrapper function (initWindowsApp) to create and
        //initialize the main application window
        //passing in the hInstance and nShowCmd
        //values as arguments.
        if (!InitWindowsApp(hInstance, nShowCmd)) {
            return 0;
        }

        //enter message loop. stay until WM_QUIT received, terminates application
        return Run();
    



        mem.CleanUp();
    }

    bool InitWindowsApp(HINSTANCE instanceHandle, int show)
    {
        //first task to creating window is to describe characteristics using WNDCLASS structure
        WNDCLASS wc;

        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = instanceHandle;
        wc.hIcon = LoadIcon(0, IDI_APPLICATION);
        wc.hCursor = LoadCursor(0, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wc.lpszMenuName = 0;
        wc.lpszClassName = L"BasicWndClass";

        //regist this wndclass instance with windows
        //so that a window can be created

        if (!RegisterClass(&wc)) {
            MessageBox(0, L"RegisterClass FAILED", 0, 0);
            return false;
        }

        //create window
        //this function returns a handle to the window
        //many WIN32 API functions dealing with windows
        //require an HWND to know what window to act on.

        ghMainWnd = CreateWindow(L"BasicWndClass",
            L"Wnd32Basic",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0, 0, instanceHandle, 0);

        if (ghMainWnd == 0)
        {
            MessageBox(0, L"CreateWindow FAILED", 0, 0);
            return false;
        }

        //window not initually shown
        //show and update
        //pass handle to the window we want to affect

        ShowWindow(ghMainWnd, show);
        UpdateWindow(ghMainWnd);

        return true;
    }

    int Run() {

        MSG msg = { 0 };

        //loop until WM_QUIT
        //GetMessage puts application to sleep until message
        BOOL bRet = 1;
        while ((bRet = GetMessage(&msg, 0, 0, 0)) != 0) {

            if (bRet == -1)
            {
                MessageBox(0, L"GetMessage FAILED", L"Error", MB_OK);
                break;
            }

            else {

                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }

        return (int)msg.wParam;
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        //handle some specific messages
        //return 0 when handling a message
        switch (msg)
        {
            //left mouse button
        case WM_LBUTTONDOWN:
            MessageBox(0, L"Hello, World", L"Hello,", MB_OK);
            return 0;
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE)
                DestroyWindow(ghMainWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        }

        //forward any messages not handled to
        //the default window procedure.
        //must return DefWindowProc
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

 



