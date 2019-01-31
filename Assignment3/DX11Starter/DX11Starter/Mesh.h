#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include "Vertex.h"

#include <DirectXMath.h> 

class Mesh
{
private: 
	ID3D11Buffer* m_pVertBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	int m_nIndexCount; //Specifies how manf indices are in the index buffer

public:
	Mesh(Vertex* a_pVertex, int a_nVertexCount, int* a_pIndices, int a_nIndexCount, ID3D11Device* a_pDevice);
	~Mesh();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

	int GetIndexCount();
};

