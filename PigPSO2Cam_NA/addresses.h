#pragma once
#include <cstdint>
#include <vector>

static DWORD fovAddress;

static uintptr_t fovPtrAddress = 0x143B9B340;//0x143ADBCB8;
static std::vector<unsigned int> fovOffsets_1 = { 0x68, 0x30, 0x70, 0x30, 0x2cb0 };
static std::vector<unsigned int> fovOffsets_3 = { 0x68, 0x30, 0x70, 0x30, 0x0, 0x0, 0x800 };
static std::vector<unsigned int> fovOffsets_2 = { 0x68, 0x30, 0x70, 0x30, 0x0, 0x0, 0xCB0 };
static std::vector<unsigned int> fovOffsets_4 = { 0x68, 0x30, 0x70, 0x30, 0x0, 0x0, 0x1480};



//tbd
/*
pso2.exe + 18C8A70: 41 0F29 73 D8 - movaps[r11 - 28], xmm6
pso2.exe + 18C8A75 : 41 0F29 7B C8 - movaps[r11 - 38], xmm7
pso2.exe + 18C8A7A : 45 0F29 43 B8 - movaps[r11 - 48], xmm8
pso2.exe + 18C8A7F : 45 0F29 4B A8 - movaps[r11 - 58], xmm9
pso2.exe + 18C8A84 : F3 44 0F10 0D 433EA301 - movss xmm9, [1432FC8D0]
pso2.exe + 18C8A8D : 45 0F29 53 98 - movaps[r11 - 68], xmm10
pso2.exe + 18C8A92 : F3 44 0F10 15 09B07001 - movss xmm10, [142FD3AA4]
pso2.exe + 18C8A9B: 45 0F29 A3 78FFFFFF - movaps[r11 - 00000088], xmm12
pso2.exe + 18C8AA3 : 4C 39 71 48 - cmp[rcx + 48], r14
pso2.exe + 18C8AA7 : 0F84 3B010000 - je 1418C8BE8
// ---------- INJECTING HERE ----------
pso2.exe + 18C8AAD : 4C 39 35 04222102 - cmp[143ADACB8], r14
// ---------- DONE INJECTING  ----------
pso2.exe + 18C8AB4 : 0F84 2E010000 - je 1418C8BE8
pso2.exe + 18C8ABA : 4C 39 B6 80010000 - cmp[rsi + 00000180], r14
pso2.exe + 18C8AC1 : 0F84 21010000 - je 1418C8BE8
pso2.exe + 18C8AC7 : 48 8B 0D F2212102 - mov rcx, [143ADACC0]
pso2.exe + 18C8ACE : 48 85 C9 - test rcx, rcx
pso2.exe + 18C8AD1 : 0F84 11010000 - je 1418C8BE8
pso2.exe + 18C8AD7 : E8 F4E43C01 - call 142C96FD0
pso2.exe + 18C8ADC : 48 8B 86 20010000 - mov rax, [rsi + 00000120]
pso2.exe + 18C8AE3 : 4C 8D 05 F6EA8101 - lea r8, [1430E75E0]
pso2.exe + 18C8AEA : 48 8D 54 24 78 - lea rdx, [rsp + 78]
*/
