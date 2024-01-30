#include "IDrawable.h"

#include <iostream>

void IDrawable::Draw(Graphics& gfx)
{
	for (auto& bind : bindables)
	{
		bind->Bind(gfx);
	}

	gfx.DrawIndexed(pIndexBuffer->GetCount());
}

void IDrawable::AddBind(std::unique_ptr<IBindable> bind)
{
	if (typeid(bind) == typeid(IndexBuffer))
	{
		std::cout << "Must use AddIndexBuffer to bind index buffer" << std::endl;
		return;
	}

	bindables.push_back(std::move(bind));
}

void IDrawable::AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer)
{
	pIndexBuffer = indexBuffer.get();
	bindables.push_back(std::move(indexBuffer));
}