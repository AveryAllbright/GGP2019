#pragma once
#include "Mesh.h"
#include "Material.h"
#include <DirectXMath.h>

using vec3 = DirectX::XMFLOAT3;
using mat4 = DirectX::XMFLOAT4X4;

class Entity
{
private: 
	
	vec3 m_vRotation;
	vec3 m_vScale;
	vec3 m_vPos;
	mat4 m_mWorld;
	Mesh* m_pMesh;
	Material* m_pMaterial;

	bool m_bDirty = false;

public:
	
	Entity(Mesh* a_pMesh, Material* a_pMaterial, mat4 a_mWorld, vec3 a_vPos, vec3 a_vRot, vec3 a_vScale);
	void SetRotation(vec3 a_vRotation);
	void SetScale(vec3 a_vScale);
	void SetPos(vec3 a_vPos);
	void SetWorld(mat4 a_mWorld);
	void PrepareMaterial(mat4 a_mView, mat4 a_mProj);

	vec3 GetRotation();
	vec3 GetScale();
	vec3 GetPos();
	mat4 GetWorld();
	Mesh* GetMesh();

	void Move(vec3 a_vDisplaceBy);
	void UpdateWorldView();
	void RotateBy(vec3 a_vRotation);
	void ScaleBy(vec3 a_vScale);

	Material * GetMat();

	virtual ~Entity();
};

