#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

class App
{
public:
	App();
	~App();
public:
	void Create(HWND hwnd);
	void Render(void);
	void CleanUp(void);

private:
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 device;
	int width, height;
};