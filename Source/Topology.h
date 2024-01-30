#pragma once

#include "IBindable.h"

class Topology : public IBindable
{
private:
	D3D11_PRIMITIVE_TOPOLOGY type;

public:
	Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Graphics& gfx);
};

