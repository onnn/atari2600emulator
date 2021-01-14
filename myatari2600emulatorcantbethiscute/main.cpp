#include <iostream>
#include <windows.h>
#include "CPU.h"
#include "MEM.h"
#include "UI.h"


//Must include command line parameters for main to be recognized by SDL

    //Main window handle; used to identify a created window.
    MEM mem;
    CPU cpu;
    UI ui;

    int WINAPI WinMain(HINSTANCE, //hInstance
        HINSTANCE, //hPrevInstance
        LPSTR, //lpCmdLine
        int //nCmdShow
    )
    {

        mem.AllocateMemory("b.a26");
        cpu.Init();
        //first call our wrapper function (initWindowsApp) to create and
        //initialize the main application window
        //passing in the hInstance and nShowCmd
        //values as arguments.
        HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

        if (SUCCEEDED(CoInitialize(NULL)))
        {

            {
                UI ui;
                if (SUCCEEDED(ui.InitWindowsApp()))
                {
                    ui.Run();
                }
            }
            CoUninitialize();
        }


        mem.CleanUp();
        return 0;
    }

   
 



