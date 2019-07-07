/*
    Beginning DirectX 11 Game Programming
    By Allen Sherrod and Wendy Jones

    DX11DemoBase Class - Base class for all demos to derive from.
*/


#ifndef _DEMO_BASE_H_
#define _DEMO_BASE_H_

#include <d3d11.h>

class DX11DemoBase
{
    public:
        DX11DemoBase();
        virtual ~DX11DemoBase();

        bool Initialize( HINSTANCE hInstance, HWND hwnd );
        void Shutdown( );

        bool CompileD3DShader( char* filePath, char* entry,
                               char* shaderModel, ID3DBlob** buffer );

        virtual bool LoadContent( );
        virtual void UnloadContent( );

        virtual void Update( float dt ) = 0;
        virtual void Render( ) = 0;

    protected:
        HINSTANCE hInstance_;
        HWND hwnd_;

        D3D_DRIVER_TYPE driverType_;
        D3D_FEATURE_LEVEL featureLevel_;

        ID3D11Device* d3dDevice_;
        ID3D11DeviceContext* d3dContext_;
        IDXGISwapChain* swapChain_;
        ID3D11RenderTargetView* backBufferTarget_;
};

#endif