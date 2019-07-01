#include "DemoApp.h"
#include <stdio.h>

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

	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	rect.bottom=0;
	width = 0;
	height = 0;

	clientRect.left = 0;
	clientRect.top = 0;
	clientRect.right = 0;
	clientRect.bottom = 0;

	fps = 0.0;
	frameCount = 0;
	tickCurrent = 0;
	tickLast = 0;
}

App::~App()
{
	CleanUp();
}

void App::Create(HWND hwnd)
{
	::GetWindowRect(hwnd, &rect);
	width= rect.right - rect.left;
	height = rect.bottom - rect.top;  
	clientRect.right = width;
	clientRect.bottom = height;

	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;

	LPDIRECT3D9 dx = Direct3DCreate9(D3D_SDK_VERSION);

	dx->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device);

	dx->Release();

	D3DXCreateFont(device, 36, 0, 0, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 0, "微软雅黑", &pFont);
}

void App::Render()
{
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 128), 1.0f, 0);
	device->BeginScene();                 

	Rotate();

	if (::GetAsyncKeyState(0x31) & 0x8000f)         // 若数字键1被按下，进行线框填充
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	if (::GetAsyncKeyState(0x32) & 0x8000f)         // 若数字键2被按下，进行实体填充
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	device->SetStreamSource(0, pVertexBuffer, 0, sizeof(CUSTOMVERTEX));//把包含的几何体信息的顶点缓存和渲染流水线相关联
	device->SetFVF(D3DFVF_CUSTOMVERTEX);//指定我们使用的灵活顶点格式的宏名称
	device->SetIndices(pIndexBuffer);//设置索引缓存
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);//利用索引缓存配合顶点缓存绘制图形

	int ct=sprintf_s(szFPS, 32, "FPS:%08.3f", GetFPS());
	pFont->DrawText(NULL, szFPS, ct, &clientRect, DT_TOP|DT_RIGHT , D3DCOLOR_XRGB(255, 0, 255));
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

void App::CleanUp()
{
	if (device != NULL)
	{
		device->Release();
		device = NULL;
	}
}

double App::GetFPS()
{
	++frameCount;
	tickCurrent = GetTickCount();
	double delta = ((double)(tickCurrent - tickLast)) / 1000.0;
	if (delta > 1.0) 
	{
		fps = ((double)frameCount) / delta;
		tickLast = tickCurrent;
		frameCount = 0;
	}

	return fps;
}

void App::InitObjects()
{
	//创建顶点缓存
	device->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT, &pVertexBuffer, NULL);
	// 创建索引缓存
	device->CreateIndexBuffer(36 * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIndexBuffer, NULL);
	
	CUSTOMVERTEX Vertices[] =
	{
		{ -20.0f, 20.0f, -20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -20.0f, 20.0f, 20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 20.0f, 20.0f, 20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 20.0f, 20.0f, -20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -20.0f, -20.0f, 20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 20.0f, -20.0f, 20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

	};

	//填充顶点缓存
	VOID* pVertices;
	pVertexBuffer->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);
	memcpy(pVertices, Vertices, sizeof(Vertices));
	pVertexBuffer->Unlock();

	// 填充索引数据
	WORD *pIndices = NULL;
	pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);

	// 顶面
	pIndices[0] = 0, pIndices[1] = 1, pIndices[2] = 2;
	pIndices[3] = 0, pIndices[4] = 2, pIndices[5] = 3;
	// 正面
	pIndices[6] = 0, pIndices[7] = 3, pIndices[8] = 7;
	pIndices[9] = 0, pIndices[10] = 7, pIndices[11] = 4;
	// 左侧面
	pIndices[12] = 0, pIndices[13] = 4, pIndices[14] = 5;
	pIndices[15] = 0, pIndices[16] = 5, pIndices[17] = 1;
	// 右侧面
	pIndices[18] = 2, pIndices[19] = 6, pIndices[20] = 7;
	pIndices[21] = 2, pIndices[22] = 7, pIndices[23] = 3;
	// 背面
	pIndices[24] = 2, pIndices[25] = 5, pIndices[26] = 6;
	pIndices[27] = 2, pIndices[28] = 1, pIndices[29] = 5;
	// 底面
	pIndices[30] = 4, pIndices[31] = 6, pIndices[32] = 5;
	pIndices[33] = 4, pIndices[34] = 7, pIndices[35] = 6;
	pIndexBuffer->Unlock();

	device->SetRenderState(D3DRS_LIGHTING, FALSE);      //关闭光照
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);   //开启背面消隐
}

void App::Rotate()
{
	D3DXMATRIX matWorld, Rx, Ry, Rz;
	D3DXMatrixIdentity(&matWorld);                
	D3DXMatrixRotationX(&Rx, D3DX_PI *(::timeGetTime() / 1000.0f));   
	D3DXMatrixRotationY(&Ry, D3DX_PI *(::timeGetTime() / 1000.0f / 2));   
	D3DXMatrixRotationZ(&Rz, D3DX_PI *(::timeGetTime() / 1000.0f / 3));   
	matWorld = Rx * Ry * Rz * matWorld;            
	device->SetTransform(D3DTS_WORLD, &matWorld);  

	D3DXMATRIX matView;
	D3DXVECTOR3 vEye(0.0f, 0.0f, -200.0f);  
	D3DXVECTOR3 vAt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp); 
	device->SetTransform(D3DTS_VIEW, &matView); 

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, 1.0f, 1.0f, 1000.0f);
	device->SetTransform(D3DTS_PROJECTION, &matProj);  

	D3DVIEWPORT9 vp; 
	vp.X = 0;		
	vp.Y = 0;		
	vp.Width = width;	
	vp.Height = height;
	vp.MinZ = 0.0f; 
	vp.MaxZ = 1.0f;	
	device->SetViewport(&vp); 
}