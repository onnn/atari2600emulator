#include <iostream>
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
int main(int argc, char** args) {

    MEM mem;
    CPU cpu;

    mem.AllocateMemory("b.a26");
    cpu.Init();  
    while (1) {
        cpu.Step();
    }
    mem.CleanUp();

    return 0;

}

