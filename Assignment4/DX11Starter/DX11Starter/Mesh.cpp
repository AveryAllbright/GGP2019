#include "Mesh.h"


Mesh::Mesh(Vertex * a_pVertex, int a_nVertexCount, int * a_pIndices, int a_nIndexCount, ID3D11Device * a_pDevice)
{
	//Create Vertex Buffer Description
	// Made on the stack since we only need it in order to make the buffer
	//After that, it's useless
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * a_nVertexCount; //set aside memory for all the vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Sets the buffer as a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	//struct to hold initial vertex data
	//aka how we fill the buffer

	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = a_pVertex;

	//Actually create the buffer
	//Permanently sets the buffer
	a_pDevice->CreateBuffer(&vbd, &initialVertexData, &m_pVertBuffer);


	//Create Index Buffer Description
	D3D11_BUFFER_DESC ibd; 
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * a_nIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	//struct to hold inital index data
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = a_pIndices;

	//Create the buffer
	a_pDevice->CreateBuffer(&ibd, &initialIndexData, &m_pIndexBuffer);

	m_nIndexCount = a_nIndexCount;
}

Mesh::~Mesh()
{
	if (m_pVertBuffer) { m_pVertBuffer->Release(); }
	if (m_pIndexBuffer) { m_pIndexBuffer->Release(); }
}

ID3D11Buffer * Mesh::GetVertexBuffer()
{
	return m_pVertBuffer;
}

ID3D11Buffer * Mesh::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

int Mesh::GetIndexCount()
{
	return m_nIndexCount;
}
