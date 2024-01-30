#include "Graphics.h"

Graphics::Graphics(HWND hWnd, int width, int height)
{
	// Swap chain description
	DXGI_SWAP_CHAIN_DESC scd{};
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = NULL;
	
	// Create devices and the swap Chain
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&pSC,
		&pDevice,
		nullptr,
		&pContext
	);

	// Create viewport
	D3D11_VIEWPORT viewport{};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// Set viewport
	pContext->RSSetViewports(1, &viewport);

	// Get the back buffer
	MWRL::ComPtr<ID3D11Resource> pBackBuffer;
	pSC->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);

	// Create render target view
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pRTV);

	// Depth stencil state description
	D3D11_DEPTH_STENCIL_DESC dsd{};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;

	// Create and bind depth stencil state
	MWRL::ComPtr<ID3D11DepthStencilState> pDSS;
	pDevice->CreateDepthStencilState(&dsd, &pDSS);
	pContext->OMSetDepthStencilState(pDSS.Get(), 1);

	// Depth stencil texture description
	D3D11_TEXTURE2D_DESC t2dd{};
	t2dd.Width = width;
	t2dd.Height = height;
	t2dd.MipLevels = 1;
	t2dd.ArraySize = 1;
	t2dd.Format = DXGI_FORMAT_D32_FLOAT;
	t2dd.SampleDesc.Count = 1;
	t2dd.SampleDesc.Quality = 0;
	t2dd.Usage = D3D11_USAGE_DEFAULT;
	t2dd.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// Create depth stencil texture
	MWRL::ComPtr<ID3D11Texture2D> pDST;
	pDevice->CreateTexture2D(&t2dd, nullptr, &pDST);

	// Depth stencil view description
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd{};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	// Create depth stencil view
	pDevice->CreateDepthStencilView(pDST.Get(), &dsvd, &pDSV);

	// Bind render target view and depth stencil view
	pContext->OMSetRenderTargets(1, pRTV.GetAddressOf(), pDSV.Get());
}

void Graphics::Clear(float r, float g, float b)
{
	float bg[4] = { r, g, b, 1.0f };
	pContext->ClearRenderTargetView(pRTV.Get(), bg);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Graphics::Present()
{
	pSC->Present(0, 0);
}