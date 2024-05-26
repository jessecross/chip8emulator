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
    unsigned short indexReg;    // Index Register (for memory addresses) that can take any value from 0x000 to 0xFFF (0-4095)
    unsigned short pc;          // Program Counter to store address of next instruction, similarly any value from 0x000 to 0xFFF (0-4095)

    unsigned short stack[16]; // Stack of 16 levels to remember current position before jump or subroutine call (by the operation codes)
    unsigned short sp;        // Stack pointer to remember which level of the stack is used

    unsigned char key[16]; // HEX based keypad (0x0-0xF) - array used to store current key state

    void assignMemory();
};

class Operations
{
public:
    void executeOpCode(const unsigned char *memory, const unsigned short &pc);

private:
    unsigned short opCode;
    struct opCodeFunction
    {
        const std::string mnemonic;
        std::function<void()> function;
    };
    static std::unordered_map<const unsigned short, opCodeFunction> opCodeMap;
};