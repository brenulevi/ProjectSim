#pragma once

#include <vector>
#include <memory>

#include "IBindable.h"
#include "IndexBuffer.h"

class IDrawable
{
private:
	std::vector<std::unique_ptr<IBindable>> bindables;
	IndexBuffer* pIndexBuffer;

public:
	void Draw(Graphics& gfx);
	void AddBind(std::unique_ptr<IBindable> bind);
	void AddIndexBuffer(std::unique_ptr<IndexBuffer> indexBuffer);

	virtual void Update(float deltaTime) = 0;
	virtual DX::XMMATRIX GetTransformMatrix() = 0;
};