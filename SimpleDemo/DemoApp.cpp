#include "DemoApp.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")   // PlaySound 

App::App()
{
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	width = 0;
	height = 0;
}

App::~App()
{
	CleanUp();
}

void App::Create(HWND hwnd)
{
	RECT rect;
	::GetWindowRect(hwnd, &rect);
	width= rect.right - rect.left;
	height = rect.bottom - rect.top; 

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;

	LPDIRECT3D9 dx = Direct3DCreate9(D3D_SDK_VERSION);

	dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device);

	dx->Release();
}

void App::Render()
{

}

void App::CleanUp()
{
	if (device != NULL)
	{
		device->Release();
		device = NULL;
	}
}