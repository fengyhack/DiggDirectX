#include "DemoApp.h"
#include "resource.h"


HWND CreateSimpleWindow(HINSTANCE hInstance, LPCSTR lpszClx, WNDPROC wndProc, BOOL fullScreen = false);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

App app;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LPCSTR lpsz = "CubeDemo-Advanced";
	HWND hwnd = CreateSimpleWindow(hInstance, lpsz, WndProc);		

	app.Create(hwnd);
	app.InitObjects();
	app.PlayMusic("Background.mp3");

	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	MSG msg = { 0 };  
	while (msg.message != WM_QUIT)			
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   
		{
			TranslateMessage(&msg);		
			DispatchMessage(&msg);		
		}
		else
		{
			app.Render();
		}
	}

	//app.Release(); 	// 当app对象生命期结束时会自动调用Release()

	UnregisterClass(lpsz, hInstance);  

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)						
	{
	case WM_PAINT:			
		app.Render();
		break;

	case WM_KEYDOWN:					
		if (wParam == VK_ESCAPE)
		{
			DestroyWindow(hwnd);
		}
		break;									

	case WM_DESTROY:		
		PostQuitMessage(0);			
		break;									

	default:									
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND CreateSimpleWindow(HINSTANCE hInstance, LPCSTR lpszClx, WNDPROC wndProc, BOOL fullScreen)
{
	WNDCLASSEX wcex = { 0 };							
	wcex.cbSize = sizeof(WNDCLASSEX);			
	wcex.style = CS_HREDRAW | CS_VREDRAW;	
	wcex.lpfnWndProc = wndProc;				
	wcex.cbClsExtra = 0;							
	wcex.cbWndExtra = 0;						
	wcex.hInstance = hInstance;					
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);   
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 255));
	wcex.lpszMenuName = NULL;					
	wcex.lpszClassName = lpszClx;

	if (!RegisterClassEx(&wcex))
	{
		throw("Failed to register \'Demo\' window class");
	}

	int left = 0;
	int top = 0;
	int width = 800;
	int height = 600;
	int scx = ::GetSystemMetrics(SM_CXSCREEN);
	int scy = ::GetSystemMetrics(SM_CYSCREEN);
	DWORD style = WS_OVERLAPPEDWINDOW;

	if (fullScreen)
	{
		width = scx;
		height = scy;
		style = WS_POPUP;
	}
	else
	{
		left = (::GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		top = 50;
	}

	return CreateWindow(lpszClx, lpszClx, style, left, top , width, height, NULL, NULL, hInstance, NULL);
}