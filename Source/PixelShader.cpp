#include "PixelShader.h"

PixelShader::PixelShader(Graphics& gfx, const std::wstring& file)
{
	MWRL::ComPtr<ID3D10Blob> blob;

	D3DCompileFromFile(file.c_str(), nullptr, nullptr, "main", "ps_5_0", NULL, NULL, &blob, nullptr);

	gfx.GetDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Graphics& gfx)
{
	gfx.GetContext()->PSSetShader(pPixelShader.Get(), nullptr, 0);
}