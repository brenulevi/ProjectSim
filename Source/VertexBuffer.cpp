#include "VertexBuffer.h"

void VertexBuffer::Bind(Graphics& gfx)
{
	const unsigned int offset = 0;
	gfx.GetContext()->IASetVertexBuffers(0, 1, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
