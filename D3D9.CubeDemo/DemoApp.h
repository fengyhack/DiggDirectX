#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

class App
{
public:
	App();
	~App();
public:
	void Create(HWND hwnd);
	void Render(void);
	void CleanUp(void);

	void InitObjects(void);
	void Rotate(void);

	double GetFPS();

private:
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 device;
	ID3DXFont*  pFont;
	char szFPS[32];

	LPDIRECT3DVERTEXBUFFER9		pVertexBuffer = NULL;    //顶点缓冲区对象
	LPDIRECT3DINDEXBUFFER9		pIndexBuffer = NULL;    // 索引缓存对象

	RECT rect;
	RECT clientRect;
	int width, height;
	double fps;
	int frameCount;
	DWORD tickCurrent;
	DWORD tickLast;
};