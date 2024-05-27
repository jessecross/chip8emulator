#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include "cpu.h"

// Initialize registers and memory once
void chip8::initialise()
{
    // TODO
}

void chip8::assignMemory()
{
    // TODO
    // 0-511 used for Chip8 interpretor (font set in EMU)
    // 80-160 used for the built in 4x5 pixel font set (0-F)
    // 512-4095 used for Program ROM and work RAM
}

// Load a game into memory
void chip8::loadGame(const std::string &name)
{
    // TODO
}

/*
Every cycle, the method emulateCycle is called which emulates one cycle of the Chip 8 CPU. During this cycle, the emulator will Fetch, Decode and Execute one opcode.
*/
void chip8::emulateCycle()
{
    // Fetch Opcode
    // Decode Opcode
    // Execute Opcode

    // Update timers
}

// If we press or release a key, we should store this state in the part that emulates the keypad
void chip8::setKeys()
{
    // TODO
}

Operations::Operations()
{
    opCodeTable[0x0]{&Operations::OP_opCodeTable0};
    opCodeTable[0x1]{&Operations::OP_1nnn};
    opCodeTable[0x2]{&Operations::OP_2nnn};
    opCodeTable[0x3]{&Operations::OP_3xkk};
    opCodeTable[0x4]{&Operations::OP_4xkk};
    opCodeTable[0x5]{&Operations::OP_5xy0};
    opCodeTable[0x6]{&Operations::OP_6xkk};
    opCodeTable[0x7]{&Operations::OP_7xkk};
    opCodeTable[0x8]{&Operations::OP_opCodeTable8};
    opCodeTable[0x9]{&Operations::OP_9xy0};
    opCodeTable[0xA]{&Operations::OP_Annn};
    opCodeTable[0xB]{&Operations::OP_Bnnn};
    opCodeTable[0xC]{&Operations::OP_Cxkk};
    opCodeTable[0xD]{&Operations::OP_Dxyn};
    opCodeTable[0xE]{&Operations::OP_opCodeTableE};
    opCodeTable[0xF]{&Operations::OP_opCodeTableF};

    for (size_t i = 0; i <= 0xE; i++)
    {
        opCodeTable0[i]{&Operations::OP_NULL};
        opCodeTable8[i]{&Operations::OP_NULL};
        opCodeTableE[i]{&Operations::OP_NULL};
    }

    for (size_t i = 0; i <= 0x65; i++)
    {
        opCodeTableF[i]{&Operations::OP_NULL};
    }

    opCodeTable0[0x0]{&Operations::OP_00E0};
    opCodeTable0[0xE]{&Operations::OP_00EE};

    opCodeTable8[0x0]{&Operations::OP_8xy0};
    opCodeTable8[0x1]{&Operations::OP_8xy1};
    opCodeTable8[0x2]{&Operations::OP_8xy2};
    opCodeTable8[0x3]{&Operations::OP_8xy3};
    opCodeTable8[0x4]{&Operations::OP_8xy4};
    opCodeTable8[0x5]{&Operations::OP_8xy5};
    opCodeTable8[0x6]{&Operations::OP_8xy6};
    opCodeTable8[0x7]{&Operations::OP_8xy7};
    opCodeTable8[0xE]{&Operations::OP_8xyE};

    opCodeTableE[0xA1]{&Operations::OP_ExA1};
    opCodeTableE[0x9E]{&Operations::OP_Ex9E};

    opCodeTableF[0x07]{&Operations::OP_Fx07};
    opCodeTableF[0x0A]{&Operations::OP_Fx0A};
    opCodeTableF[0x15]{&Operations::OP_Fx15};
    opCodeTableF[0x18]{&Operations::OP_Fx18};
    opCodeTableF[0x1E]{&Operations::OP_Fx1E};
    opCodeTableF[0x29]{&Operations::OP_Fx29};
    opCodeTableF[0x33]{&Operations::OP_Fx33};
    opCodeTableF[0x55]{&Operations::OP_Fx55};
    opCodeTableF[0x65]{&Operations::OP_Fx65};
}

void Operations::executeOpCode(const unsigned char *memory, const unsigned short &pc)
{
    opCode = (memory[pc] << 8) | memory[pc + 1]; // e.g. 0x00, 0xE0 -> 0x00E0

    try
    {
        ((*this).*(opCodeTable[(opCode & 0xF000) >> 12]))(); // e.g. 0x1AAA -> 0x1000 -> 0x1
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "opCode " << opCode << " does not exist." << std::endl;
    }
}
