#pragma once

#include <string>
#include <d3dcompiler.h>

#include "IBindable.h"

class PixelShader : public IBindable
{
private:
	MWRL::ComPtr<ID3D11PixelShader> pPixelShader;

public:
	PixelShader(Graphics& gfx, const std::wstring& file);

	void Bind(Graphics& gfx);
};