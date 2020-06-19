#pragma once
#include "dxhook.h"
#include "settings_form.h"

#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"

bool m_bCreated = false;
D3DVIEWPORT9 viewport;

HWND game_hwnd = 0;

static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

typedef HRESULT(__stdcall* tEndScene)(LPDIRECT3DDEVICE9 Device);
tEndScene oEndScene;
typedef HRESULT(__stdcall* tReset)(LPDIRECT3DDEVICE9 Device, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset;

WNDPROC game_wndproc = NULL;
extern IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static bool MENU_DISPLAYING = false;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) || (MENU_DISPLAYING))
	{
		/*if (MENU_DISPLAYING && msg == WM_KEYDOWN && wParam == VK_ESCAPE) {
			MENU_DISPLAYING = false;
		}*/
		return true;
	}

	return CallWindowProc(game_wndproc, hWnd, msg, wParam, lParam);
}

HRESULT __stdcall hkEndScene(LPDIRECT3DDEVICE9 Device)
{
	if (Device == nullptr)
		return oEndScene(Device);
	if (!m_bCreated)
	{
		m_bCreated = true;
		Device->GetViewport(&viewport);

		D3DDEVICE_CREATION_PARAMETERS CParams;
		Device->GetCreationParameters(&CParams);
		game_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(CParams.hFocusWindow, GWLP_WNDPROC, (LONG_PTR)WndProc));

		menu_init(game_hwnd, Device);
	}

	if ((GetAsyncKeyState(0x2D) & 1)) { //insert
		MENU_DISPLAYING = !MENU_DISPLAYING;
	}
	if (MENU_DISPLAYING)
	{
		draw_menu(&MENU_DISPLAYING);
	}

	return oEndScene(Device);
}

HRESULT APIENTRY hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	HRESULT result = oReset(pDevice, pPresentationParameters);
	if (SUCCEEDED(result))
	{
		m_bCreated = false;
		ImGui_ImplDX9_InvalidateDeviceObjects();
		pDevice->GetViewport(&viewport);

		ImGui_ImplDX9_CreateDeviceObjects();
	}
	return result;
}



BOOL CALLBACK find_game_hwnd(HWND hwnd, LPARAM game_pid) {
	DWORD hwnd_pid = NULL;
	GetWindowThreadProcessId(hwnd, &hwnd_pid);
	if (hwnd_pid != game_pid)
		return TRUE;
	game_hwnd = hwnd;
	return FALSE;
}

DWORD64* dVtable;
bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		//printf("D3D Failure to Init\n");
		return false;
	}

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	g_d3dpp.hDeviceWindow = hWnd;
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	HRESULT ret = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice);
	if (FAILED(ret)) { 
	
		return false;
	}

	dVtable = (DWORD64*)g_pd3dDevice;
	dVtable = (DWORD64*)dVtable[0];
	return true;
}

DWORD WINAPI installDXHooks()
{
	while (GetModuleHandleA("d3d9.dll") == NULL)
	{
		Sleep(100);
	}	
	EnumWindows(find_game_hwnd, GetCurrentProcessId());
	CreateDeviceD3D(game_hwnd);

	if (!dVtable)
		return false;


	oEndScene = (tEndScene)dVtable[42];
	oReset = (tReset)dVtable[16];

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)oEndScene, (PBYTE)hkEndScene);
	DetourAttach(&(LPVOID&)oReset, (PBYTE)hkReset);
	DetourTransactionCommit();

	return 0;
}