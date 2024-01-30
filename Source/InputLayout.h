#pragma once

#include <vector>

#include "IBindable.h"

class InputLayout : public IBindable
{
private:
	MWRL::ComPtr<ID3D11InputLayout> pInputLayout;

public:
	InputLayout(Graphics& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC> ied, ID3D10Blob*& vsBlob);

	void Bind(Graphics& gfx);
};

