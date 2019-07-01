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
	void PlayMusic(char* pszMusicFile,BOOL soundEffect=FALSE);
	void Render(void);
	void Release(void);

	void InitObjects(void);
	void Rotate(void);

	void KeyboardInputAsync(void);

	double GetFPS();

private:
	D3DPRESENT_PARAMETERS d3dpp;
	LPDIRECT3DDEVICE9 device;
	ID3DXFont*  pFont;
	char szFPS[FPS_CHAR_LEN];

	LPDIRECT3DVERTEXBUFFER9		pVertexBuffer;    //顶点缓冲区对象
	LPDIRECT3DINDEXBUFFER9		pIndexBuffer;    // 索引缓存对象

	ISoundEngine*  soundEngine;
	ISoundSource* soundSource;
	ISound* bkMusic;
	ISoundEffectControl* soundFx;
	BOOL soundEffect;


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

	D3DCOLOR crBackground;
};