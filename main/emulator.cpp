#include <iostream>
#include "cpu.h"
#include "graphics.h"
#include "input.h"

// Load chip8 CPU implemtation
chip8 myChip8;

int main (int argc, char **argv) 
{

    // Set up render system
    setupGraphics();

    // Register input callbacks
    setupInput();

    // Initialise chip8 system
    myChip8.initialise();

    // Load game
    myChip8.loadGame("pong");

    // Emulation cycle
    for (;;)
    {   
        // Single Cycle
        myChip8.emulateCycle();

        // Update the screen
        if (myChip8.drawFlag)
        {
            drawGraphics();
        }

        // Store key press state (press and release)
        myChip8.setKeys();
    }

    return 0;
}