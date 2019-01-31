#include "Entity.h"


Entity::Entity(Mesh * a_pMesh, Material * a_pMaterial, mat4 a_mWorld, vec3 a_vPos, vec3 a_vRot, vec3 a_vScale) : m_pMesh(a_pMesh), m_mWorld(a_mWorld),
m_vPos(a_vPos), m_vRotation(a_vRot), m_vScale(a_vScale), m_pMaterial(a_pMaterial)
{
}

void Entity::SetRotation(vec3 a_vRotation)
{
	m_vRotation = a_vRotation;
}

void Entity::SetScale(vec3 a_vScale)
{
	m_vScale = a_vScale;
}

void Entity::SetPos(vec3 a_vPos)
{
	m_vPos = a_vPos;
}

void Entity::SetWorld(mat4 a_mWorld)
{
	m_mWorld = a_mWorld;
}

void Entity::PrepareMaterial(mat4 a_mView, mat4 a_mProj)
{
	m_pMaterial->GetVertShader()->SetMatrix4x4("world", m_mWorld);
	m_pMaterial->GetVertShader()->SetMatrix4x4("view", a_mView);
	m_pMaterial->GetVertShader()->SetMatrix4x4("projection", a_mProj);

	m_pMaterial->GetVertShader()->CopyAllBufferData();
	m_pMaterial->GetVertShader()->SetShader();
	m_pMaterial->GetPixelShader()->SetShader();
}

vec3 Entity::GetRotation()
{
	return m_vRotation;
}

vec3 Entity::GetScale()
{
	return m_vScale;
}

vec3 Entity::GetPos()
{
	return m_vPos;
}

mat4 Entity::GetWorld()
{
	return m_mWorld;
}

Mesh * Entity::GetMesh()
{
	return m_pMesh;
}

void Entity::Move(vec3 a_vDisplaceBy)
{
	m_vPos.x += a_vDisplaceBy.x;
	m_vPos.y += a_vDisplaceBy.y;
	m_vPos.z += a_vDisplaceBy.z;
}

void Entity::UpdateWorldView()
{
	DirectX::XMVECTOR trans = DirectX::XMLoadFloat3(&m_vPos);
	DirectX::XMVECTOR rotate = DirectX::XMLoadFloat3(&m_vRotation);
	DirectX::XMVECTOR scale = DirectX::XMLoadFloat3(&m_vScale);

	DirectX::XMMATRIX transl = DirectX::XMMatrixTranslationFromVector(trans);
	DirectX::XMMATRIX rotat = DirectX::XMMatrixRotationRollPitchYawFromVector(rotate);
	DirectX::XMMATRIX scal = DirectX::XMMatrixScalingFromVector(scale);

	DirectX::XMMATRIX world = scal * rotat * transl;

	DirectX::XMStoreFloat4x4(&m_mWorld, DirectX::XMMatrixTranspose(world));
}

void Entity::RotateBy(vec3 a_vRotation)
{
	m_vRotation.x += a_vRotation.x;
	m_vRotation.y += a_vRotation.y;
	m_vRotation.z += a_vRotation.z;
}

void Entity::ScaleBy(vec3 a_vScale)
{
	m_vScale.x += a_vScale.x;
	m_vScale.y += a_vScale.y;
	m_vScale.z += a_vScale.z;
}

Entity::~Entity()
{
}
