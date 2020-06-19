#pragma once
#include <Windows.h>
#include <detours.h>
#include <d3d9.h>

DWORD WINAPI installDXHooks();

static HWND dllHandle = 0;