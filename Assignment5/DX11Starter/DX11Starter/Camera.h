#pragma once
#include <DirectXMath.h>
#include <Windows.h>
class Camera
{
private:
	DirectX::XMFLOAT4X4 m_mViewMat;
	DirectX::XMFLOAT4X4 m_mProjMat;

	DirectX::XMFLOAT3 m_vPos;
	DirectX::XMFLOAT3 m_vDir;
	DirectX::XMFLOAT3 m_vFor;
	DirectX::XMFLOAT3 m_vUp;

	float m_fXRot = 0.f;
	float m_fYRot = 0.f;
	float deltX;
	float deltY;
	int trueHeight;
	int trueWidth;

public:
	Camera();
	~Camera();
	void Update(float delt);
	void Rotate(float a_fX, float a_fY, unsigned int width, unsigned int height);

	DirectX::XMFLOAT4X4 GetViewMat();
	DirectX::XMFLOAT4X4 GetProjMat();
	void SetProjection(unsigned int a_fHeight, unsigned int a_fWidth);



};