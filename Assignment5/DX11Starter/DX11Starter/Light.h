#pragma once

#include <DirectXMath.h>

struct Light
{
	DirectX::XMFLOAT4 AmbientColour;
	DirectX::XMFLOAT4 DiffuseColour;
	DirectX::XMFLOAT3 Direction;
};