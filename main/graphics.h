#ifndef GRAPHICS_H
#define GRAPHICS_H

/*
use GLUT or SDL to handle graphics and input

window size, display mode, etc) 
*/

unsigned char gfx[64 * 32]; // Screen has 2048 black/white (0/1) pixels
// Pixels are set using XOR operations
// If a pixel is turned off, the carry flag (VF register) is set (used for collision detection)

// Two timer registers that count at 60Hz, they count down to zero when set above zero
unsigned char delay_timer;
unsigned char sound_timer; // When sound_timer reaches zero, system buzzer sounds

/* Because the system does not draw every cycle, we should set a draw flag when we need to update our screen. Only two opcodes should set this flag:
0x00E0 – Clears the screen
0xDXYN – Draws a sprite on the screen
*/
void drawGraphics();

/*
Setup the graphics (window size, display mode, etc)
*/
void setupGraphics();

#endif