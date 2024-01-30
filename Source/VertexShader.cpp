#include "VertexShader.h"

VertexShader::VertexShader(Graphics& gfx, std::wstring file)
{
	D3DCompileFromFile(file.c_str(), nullptr, nullptr, "main", "vs_5_0", NULL, NULL, &pVertexShaderBlob, nullptr);

	gfx.GetDevice()->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &pVertexShader);
}

void VertexShader::Bind(Graphics& gfx)
{
	gfx.GetContext()->VSSetShader(pVertexShader.Get(), nullptr, 0);
}