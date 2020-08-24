#ifndef _TRIANGLE_DEMO_H_
#define _TRIANGLE_DEMO_H_

#include "DemoBase.h"


class TriangleDemo : public DemoBase
{
    public:
        TriangleDemo( );
        virtual ~TriangleDemo( );

        bool LoadContent( );
        void UnloadContent( );

        void Update( float dt );
        void Render( );

    private:
        ID3D11VertexShader* solidColorVS_;
        ID3D11PixelShader* solidColorPS_;

        ID3D11InputLayout* inputLayout_;
        ID3D11Buffer* vertexBuffer_;
};

#endif