#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices) :
	count(indices.size())
{
	D3D11_BUFFER_DESC bd{};
	bd.ByteWidth = UINT(sizeof(unsigned short) * count);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA bsrd{};
	bsrd.pSysMem = indices.data();

	gfx.GetDevice()->CreateBuffer(&bd, &bsrd, &pIndexBuffer);
}

void IndexBuffer::Bind(Graphics& gfx)
{
	gfx.GetContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

