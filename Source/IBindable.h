#pragma once

#include "Graphics.h"

class IBindable
{
public:
	virtual void Bind(Graphics& gfx) = 0;
	virtual ~IBindable() = default;
};