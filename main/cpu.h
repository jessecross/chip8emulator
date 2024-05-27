#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>

// A Chip8 Emulated CPU
class chip8
{
public:
    chip8();

    void initialise();
    void loadGame(const std::string &name);
    void emulateCycle();
    void setKeys();

    bool drawFlag{false};

private:
    // Abstraction of CPU hardware components
    unsigned char memory[4096]; // 4-kilobyte (4096-byte) memory
    unsigned char V[16];        // 16x 1-byte (8-bit) CPU Registers (15 general purpose and 1 carry flag / VF register)
    unsigned short I;           // Index Register (for memory addresses) that can take any value from 0x000 to 0xFFF (0-4095)
    unsigned short pc;          // Program Counter to store address of next instruction, similarly any value from 0x000 to 0xFFF (0-4095)

    unsigned short stack[16]; // Stack of 16 levels to remember current position before jump or subroutine call (by the operation codes)
    unsigned short sp;        // Stack pointer to remember which level of the stack is used

    unsigned char key[16]; // HEX based keypad (0x0-0xF) - array used to store current key state

    void assignMemory();
};

class Operations
{
public:
    Operations();

    void executeOpCode(const unsigned char *memory, const unsigned short &pc);

private:
    unsigned short opCode;

    /**
     * Create a table-of-tables pointing to member functions for the respective opCodes.
     * Where opCodes start with a repeating pattern, they are contained within a subtable.
     * All hex indexes that are not valid chip8 opCodes return the OP_NULL default function.
     */

    // Alias to the OP_* functions.
    using opCodeFunc{(void Operations::*)()};

    // Function pointer tables
    opCodeFunc opCodeTable[0xF + 1];   // Primary table (16x member functions).
    opCodeFunc opCodeTable0[0xE + 1];  // Subtable starting with 0x0 (15x member functions).
    opCodeFunc opCodeTable8[0xE + 1];  // Subtable starting with 0x8 (15x member functions).
    opCodeFunc opCodeTableE[0xE + 1];  // Subtable starting with 0xE (15x member functions).
    opCodeFunc opCodeTableF[0x65 + 1]; // Subtable starting with 0xF (102x member functions).

    // Accessors to Subtable member functions
    void OP_opCodeTable0();
    void OP_opCodeTable8();
    void OP_opCodeTableE();
    void OP_opCodeTableF();

    /**
     * Create operations per opCode.
     * Group by opCode naming patterns.
     */
    void OP_NULL(); // Default (does nothing) for when a proper opCode function is not set.

    void OP_1nnn(); // Jump to address nnn.
    void OP_2nnn(); // Call subroutine at nnn.
    void OP_3xkk(); // Skip next instruction if register Vx == constant kk.
    void OP_4xkk(); // Skip next instruction if register Vx != constant kk.
    void OP_5xy0(); // Skip next instruction if register Vx == Vy.
    void OP_6xkk(); // Set Vx to constant kk.
    void OP_7xkk(); // Add constant kk to Vx.
    void OP_9xy0(); // Skip to the next instruction if Vx != Vy.
    void OP_Annn(); // Set I to address nnn.
    void OP_Bnnn(); // Jump to address nnn + V0.
    void OP_Cxkk(); // Set Vx to the result of random number & constant kk.
    void OP_Dxyn(); // Draws sprite at position (Vx, Vy) with n bytes of data starting from address stored in I.
                    // VF set to 1 if any set pixels are changed to unset and to 0 otherwise.

    void OP_8xy0(); // Set Vx = Vy.
    void OP_8xy1(); // Set Vx |= Vy.
    void OP_8xy2(); // Set Vx &= Vy.
    void OP_8xy3(); // Set Vx ^= Vy.
    void OP_8xy4(); // Set Vx += Vy
    void OP_8xy5(); // Set Vx -= Vy.
    void OP_8xy6(); // Set Vx >>= 1.
    void OP_8xy7(); // Set Vx = Vy - Vx. And VF = 1 if Vy >= Vx (VF set to 0 when underflow and 1 when not).
    void OP_8xyE(); // Set Vx <<= 1.

    void OP_00E0(); // Clear the screen.
    void OP_00EE(); // Return from a subroutine.

    void OP_ExA1(); // Skip next instruction if key stored in Vx is not pressed.
    void OP_Ex9E(); // Skip next instruction if key stored in Vx is pressed.
    void OP_Fx07(); // Set Vx to the value of the delay timer.
    void OP_Fx0A(); // Wait for key press and store result in Vx.
    void OP_Fx15(); // Set the delay timer to Vx.
    void OP_Fx18(); // Set the sound time to Vx.
    void OP_Fx1E(); // Add Vx to I.
    void OP_Fx29(); // Set I to the location of the sprite for character in Vx.
    void OP_Fx33(); // Store binary coded decimal repr of Vx with fluff.
    void OP_Fx55(); // Store registers V0 through Vx in memory, starting at address I.
    void OP_Fx65(); // Read registers V0 through Vx from memory, starting at address I.
};