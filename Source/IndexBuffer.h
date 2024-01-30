#pragma once

#include <vector>

#include "IBindable.h"

class IndexBuffer : public IBindable
{
protected:
	MWRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	unsigned short count;

public:
	IndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	void Bind(Graphics& gfx) override;

	inline unsigned short GetCount();
};

inline unsigned short IndexBuffer::GetCount() { return count; }

