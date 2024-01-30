#pragma once

#include <string>
#include <d3dcompiler.h>

#include "IBindable.h"

class VertexShader : IBindable
{
private:
	MWRL::ComPtr<ID3D10Blob> pVertexShaderBlob;
	MWRL::ComPtr<ID3D11VertexShader> pVertexShader;

public:
	VertexShader(Graphics& gfx, std::wstring file);

	void Bind(Graphics& gfx);

	inline ID3D10Blob* getByteCode();
};

inline ID3D10Blob* VertexShader::getByteCode() { return pVertexShaderBlob.Get(); }


