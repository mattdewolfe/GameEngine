#include "Graphics\GraphicsManager.h"

GraphicsManager::GraphicsManager()
{

}

GraphicsManager::~GraphicsManager()
{ }

bool GraphicsManager::Init(int screenWidth, int screenHeight, HWND hWnd, Camera* camera)
{
	GraphicsManager::screenWidth = screenWidth;
	GraphicsManager::screenHeight = screenHeight;
	GraphicsManager::hWnd = hWnd;

	#pragma region D3Dinitialization
	// create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                    // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
    scd.OutputWindow = hWnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &swapchain,
                                  &dev,
                                  NULL,
                                  &devcon);
	#pragma endregion D3Dinitialization

	// get the address of the back buffer
    ID3D11Texture2D *pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    // use the back buffer address to create the render target
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    devcon->OMSetRenderTargets(1, &backbuffer, NULL);

	// Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
	viewport.Width = screenWidth;
	viewport.Height = screenHeight;

    devcon->RSSetViewports(1, &viewport);

	return true;
}

void GraphicsManager::EngineRender ()
{

}

void GraphicsManager::D3D_Render ()
{
	// default background colour
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.5f, 0.7f, 0.9f, 1.0f));

    swapchain->Present(0, 0);
}

void GraphicsManager::Shutdown ()
{
    swapchain->Release();
	backbuffer->Release();
    dev->Release();
    devcon->Release();
}