#pragma once
#include "SimpleShader.h"
class Material
{

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

public:
	Material(SimpleVertexShader* a_Vert, SimplePixelShader* a_Pix);
	~Material();

	SimpleVertexShader* GetVertShader();
	SimplePixelShader* GetPixelShader();

};