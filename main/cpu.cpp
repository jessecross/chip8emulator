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

void Operations::executeOpCode(const unsigned char *memory, const unsigned short &pc)
{
    opCode = memory[pc] << 8 | memory[pc + 1]; // e.g. 0x00 + 0xE0 -> 0x00E0

    try
    {
        opCodeMap.at(opCode);
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "opCode " << opCode << " does not exist." << std::endl;
    }
}

std::unordered_map<const unsigned short, Operations::opCodeFunction> Operations::opCodeMap{
    {0x00E0, {"CLS", op_CLS}},
    {0x00EE, {"RET", op_RET}},
    {0x1NNN, {"JP", op_JP}},
    {0x2NNN, {"CALL addr", op_CALL}},
    {0x3XKK, {"SE Vx, byte", [vx, kk]()
              { op_SE(vx, kk); }}},
    {0x4XKK, {"SNE Vx, byte", op_SNE}},
    {0x5XY0, {"SE Vx, Vy", op_SE}},
    {0x6XKK, {"LD Vx, byte", op_LD}},
    {0x7XKK, {"ADD Vx, byte", op_ADD}},
    {0x8XY0, {"LD Vx, Vy", op_LD}},
    {0x8XY1, {"OR Vx, Vy", op_OR}},
    {0x8XY2, {"AND Vx, Vy", op_AND}},
    {0x8XY3, {"XOR Vx, Vy", op_XOR}},
    {0x8XY4, {"ADD Vx, Vy", op_ADD}},
    {0x8XY5, {"SUB Vx, Vy", op_SUB}},
    {0x8XY6, {"SHR Vx {, Vy}", op_SHR}},
    {0x8XY7, {"SUBN Vx, Vy", op_SUBN}},
    {0x8XYE, {"SHL Vx {, Vy}", op_SHL}},
    {0x9XY0, {"SNE Vx, Vy", op_SNE}},
    {0xANNN, {"LD I, addr", op_LD}},
    {0xBNNN, {"JP V0, addr", op_JP}},
    {0xCXKK, {"RND Vx, byte", op_RND}},
    {0xDXYN, {"DRW Vx, Vy, nibble", op_DRW}},
    {0xEX9E, {"SKP Vx", op_SKP}},
    {0xEXA1, {"SKNP Vx", op_SKNP}},
    {0xFX07, {"LD Vx, DT", op_LD}},
    {0xFX0A, {"LD Vx, K", op_LD}},
    {0xFX15, {"LD DT, Vx", op_LD}},
    {0xFX18, {"LD ST, Vx", op_LD}},
    {0xFX1E, {"ADD I, Vx", op_ADD}},
    {0xFX33, {"LD B, Vx", op_LD}},
    {0xFX55, {"LD [I], Vx", op_LD}},
    {0xFX65, {"LD Vx, [I]", op_LD}},
};