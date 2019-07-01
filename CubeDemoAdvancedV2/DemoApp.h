#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <irrKlang.h>
#include <iostream>

using namespace std;
using namespace irrklang;

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

const int FPS_CHAR_LEN = 32;

class App
{
public:
	App();
	~App();

public:
	void Create(HWND hwnd);
	void InitObjects(void);
	void PlayMusic(char* pszMusicFile);
	void Render(void);
	void SafeRelease(void);

private:
	void Rotate(void);
	double GetFPS(void);
	void KeyboardInputAsync(void);
	void TrySoundEffects(void);

private:
	inline D3DCOLOR GetRandomD3DColor(void)
	{
		return D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	}
	inline BOOL IsKeyPressedAsync(int vKey)
	{
		return (BOOL)(GetAsyncKeyState(vKey) & 0x8000F );
	}

private:
	D3DPRESENT_PARAMETERS d3dpp;
	IDirect3DDevice9* device;
	IDirect3DVertexBuffer9*		pVertexBuffer;    //顶点缓冲区对象
	IDirect3DIndexBuffer9*		pIndexBuffer;    // 索引缓存对象
	ID3DXFont*  pFont;
	char szFPS[FPS_CHAR_LEN];

	ISoundEngine*  soundEngine;
	ISoundSource* soundSource;
	ISound* soundMusic;
	ISoundEffectControl* soundEfxCtrl;

private:
	RECT rect;
	RECT clientRect;
	int width, height;
	double fps;
	int frameCount;
	DWORD tickCurrent;
	DWORD tickLast;
	DWORD txtPosition;
	BOOL isReleased;
	BOOL showFPS;
	DWORD fillMode;
	D3DCOLOR crBackground;
	BOOL enableSoundEfx;
};