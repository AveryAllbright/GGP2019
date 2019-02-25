#include "Material.h"

Material::Material(SimpleVertexShader * a_Vert, SimplePixelShader * a_Pix, ID3D11ShaderResourceView * a_pSRV, ID3D11SamplerState * a_pSamp)
{
	vertexShader = a_Vert;
	pixelShader = a_Pix;
	m_pSamp = a_pSamp;
	m_pSRV = a_pSRV;
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

ID3D11SamplerState * Material::GetSamp()
{
	return m_pSamp;
}

ID3D11ShaderResourceView * Material::GetSRV()
{
	return m_pSRV;
}
