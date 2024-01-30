#include "InputLayout.h"

InputLayout::InputLayout(Graphics& gfx, std::vector<D3D11_INPUT_ELEMENT_DESC> ied, ID3D10Blob*& vsBlob)
{
	gfx.GetDevice()->CreateInputLayout(ied.data(), ied.size(), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &pInputLayout);
}

void InputLayout::Bind(Graphics& gfx)
{
	gfx.GetContext()->IASetInputLayout(pInputLayout.Get());
}