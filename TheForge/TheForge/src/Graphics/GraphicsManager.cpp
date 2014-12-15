#include "Graphics\GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	vertexCount = 0;
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
	scd.BufferDesc.Width = screenWidth;						// set the back buffer width
	scd.BufferDesc.Height = screenHeight;					// set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
    scd.SampleDesc.Count = 4;                               // how many multisamples
    scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

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

	InitPipeline();
	InitGraphics();

	return true;
}

void GraphicsManager::InitPipeline()
{
    // load and compile the two shaders
    ID3D10Blob *VS, *PS;
	// vertex shader blob object generation
    D3DX11CompileFromFile(L"Shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	// pixel shader blob object generation
    D3DX11CompileFromFile(L"Shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	// encapsulate both shaders into shader objects
    dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
    dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
    devcon->VSSetShader(pVS, 0, 0);
    devcon->PSSetShader(pPS, 0, 0);

	// create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);
}



void GraphicsManager::InitGraphics()
{
    // create a triangle using the VERTEX struct
    vertices[0] = VERTEX(0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
    vertices[1] = VERTEX(0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
    vertices[2] = VERTEX(-0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	vertexCount+=3;

    // create the vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 6;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
    memcpy(ms.pData, vertices, sizeof(vertices));                 // copy the data
    devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
}

// this is the function used to render a single frame
void GraphicsManager::RenderFrame(void)
{
    // clear the back buffer to a deep blue
    devcon->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.5f, 0.7f, 0.9f, 1.0f));

        // select which vertex buffer to display
        UINT stride = sizeof(VERTEX);
        UINT offset = 0;

		// default vertex buffer
        devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
        // select which primtive type we are using
        devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        // draw the vertex buffer to the back buffer
        devcon->Draw(vertexCount, 0);


    // switch the back buffer and the front buffer
    swapchain->Present(0, 0);
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
	pLayout->Release();
	pVS->Release();
    pPS->Release();
	pVBuffer->Release();
    swapchain->Release();
	backbuffer->Release();
    dev->Release();
    devcon->Release();
}

/*
void GraphicsManager::AddTriangle ()
{
	verticesGUI[0] = VERTEX(-1.0f, 1.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
    verticesGUI[1] = VERTEX(0.0f, 1.0, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
    verticesGUI[2] = VERTEX(-1.0f, 0.0f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	vertexCountGUI = 3;

	// copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBufferGUI, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
    memcpy(ms.pData, verticesGUI, sizeof(verticesGUI));                 // copy the data
    devcon->Unmap(pVBufferGUI, NULL);       
	// unmap the buffer
}*/