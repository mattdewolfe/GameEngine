// Much of the rendering code used was derived from http://www.directxtutorial.com/
// See the above for any discrepancies concerning directX

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <Windows.h>
#include "ECS\GameEntity.h"
#include "Camera.h"
#include <d3d11.h>
// d3dx11 and d3dx10 for extra functionality, include these if we find we need them
#include <d3dx11.h> 
#include <d3dx10.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

// function prototypes
void InitD3D(HWND hWnd);     // sets up and initializes Direct3D
void CleanD3D(void);         // closes Direct3D and releases memory

// TEMP DELETE used in tutorial, replace with our own vertex type when the time comes
// a struct to define a vertex
struct VERTEX
{
	VERTEX()
	{
		X = 0;
		Y = 0;
		Z = 0;
		Color = D3DXCOLOR(0,0,0,1);
	}
	VERTEX (float _x, float _y, float _z, D3DXCOLOR _color)
	{
		X = _x;
		Y = _y;
		Z = _z;
		Color = _color;
	}
	FLOAT X, Y, Z; D3DXCOLOR Color;
};    // a struct to define a vertex

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

	bool Init(int, int, HWND, Camera*);
	void Shutdown();
	// why did we split the render functions again?
	void EngineRender();
	void D3D_Render();
	// To alter -> Would it make more sense to only pass pointers to meshes rather than entire entities?
	void AddToRenderList(GameEntity* _e);
	void RemoveFromRenderList(GameEntity* _e);
	void InitPipeline();
	void InitGraphics();
	void GraphicsManager::RenderFrame(void);

	void GraphicsManager::AddTriangle ();

	// EARLY PROTOTYPE, REMOVE
	VERTEX vertices[6];
	UINT vertexCount;

private:
	int screenWidth, screenHeight;
	HWND hWnd;
	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
	ID3D11Device *dev;                     // the pointer to our Direct3D device interface
	ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
	ID3D11RenderTargetView *backbuffer;    // the target for rendering

	ID3D11VertexShader *pVS;    // the vertex shader
	ID3D11PixelShader *pPS;     // the pixel shader
	
	ID3D11Buffer *pVBuffer;		// vertex buffer
	ID3D11InputLayout *pLayout;	// input layout object
};
#endif
