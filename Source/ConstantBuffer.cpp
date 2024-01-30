#include "ConstantBuffer.h"

TransformConstantBuffer::TransformConstantBuffer(Graphics& gfx, IDrawable& parent)
	: 
	vertexConstantBuffer(gfx),
	parent(parent)
{
}

void TransformConstantBuffer::Bind(Graphics& gfx)
{
	vertexConstantBuffer.Update(
		gfx,
		DX::XMMatrixTranspose(
			parent.GetTransformMatrix() *
			gfx.GetProjection()
		)
	);

	vertexConstantBuffer.Bind(gfx);
}