#pragma once
#include "SimpleShader.h"
class Material
{

	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	ID3D11SamplerState* m_pSamp;
	ID3D11ShaderResourceView* m_pSRV;

public:
	Material(SimpleVertexShader* a_Vert, SimplePixelShader* a_Pix, ID3D11ShaderResourceView* a_pSRV, ID3D11SamplerState* a_pSamp);
	~Material();

	SimpleVertexShader* GetVertShader();
	SimplePixelShader* GetPixelShader();
	ID3D11SamplerState* GetSamp();
	ID3D11ShaderResourceView* GetSRV();

};