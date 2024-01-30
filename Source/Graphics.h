#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

namespace MWRL = Microsoft::WRL;
namespace DX = DirectX;

class Graphics
{
private:
	MWRL::ComPtr<ID3D11Device> pDevice;
	MWRL::ComPtr<ID3D11DeviceContext> pContext;
	MWRL::ComPtr<IDXGISwapChain> pSC;
	MWRL::ComPtr<ID3D11RenderTargetView> pRTV;
	MWRL::ComPtr<ID3D11DepthStencilView> pDSV;

	DX::XMMATRIX projection;

public:
	Graphics() = default;
	Graphics(HWND hWnd, int width, int height);
	~Graphics() = default;

	void Clear(float r, float g, float b);
	void Present();

	inline void DrawIndexed(unsigned short count);

	inline MWRL::ComPtr<ID3D11Device> GetDevice() const;
	inline MWRL::ComPtr<ID3D11DeviceContext> GetContext() const;
	inline MWRL::ComPtr<IDXGISwapChain> GetSwapChain() const;
	inline DX::XMMATRIX GetProjection();

	inline void SetProjection(DX::FXMMATRIX proj);
};

inline void Graphics::SetProjection(DX::FXMMATRIX proj) { projection = proj; }

inline void Graphics::DrawIndexed(unsigned short count) { pContext->DrawIndexed(count, 0, 0); }

inline MWRL::ComPtr<ID3D11Device> Graphics::GetDevice() const { return pDevice; }
inline MWRL::ComPtr<ID3D11DeviceContext> Graphics::GetContext() const { return pContext; }
inline MWRL::ComPtr<IDXGISwapChain> Graphics::GetSwapChain() const { return pSC; }
inline DX::XMMATRIX Graphics::GetProjection() { return projection; }

