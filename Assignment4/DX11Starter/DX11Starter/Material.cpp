#include "Material.h"

//I exist now!
//I'm a placeholder for when Emily actually decides to deal with me. 

Material::Material(SimpleVertexShader * a_Vert, SimplePixelShader * a_Pix)
{
	vertexShader = a_Vert;
	pixelShader = a_Pix;
}

Material::~Material()
{
}

SimpleVertexShader * Material::GetVertShader()
{
	return vertexShader;
}

SimplePixelShader * Material::GetPixelShader()
{
	return pixelShader;
}