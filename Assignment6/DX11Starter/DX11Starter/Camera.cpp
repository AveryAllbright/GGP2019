#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	//Set some default values 
	m_vFor = DirectX::XMFLOAT3(0, 0, 1);
	m_vUp = DirectX::XMFLOAT3(0, 1, 0);
	m_vPos = DirectX::XMFLOAT3(0, 0, -5);
	m_vDir = DirectX::XMFLOAT3(0, 0, 1);
}


Camera::~Camera()
{
}

void Camera::Update(float delt)
{
	//Rebuild rotation quat every update
	DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationRollPitchYaw(m_fXRot, m_fYRot, 0.f);

	//Build vectors for HYPER-EFFICIENT MATH 
	DirectX::XMVECTOR forward = DirectX::XMLoadFloat3(&m_vFor);
	DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&m_vUp);
	DirectX::XMVECTOR eye = DirectX::XMLoadFloat3(&m_vPos);

	//rotate the default forward by how much we rotate by...
	forward = DirectX::XMVector3Rotate(forward, quat);

	//... and then store it in our direction
	DirectX::XMStoreFloat3(&m_vDir, forward);

	//TODO : Replace delt * 3.f with float Speed = delt * SPEED_MULT;

	//Do a bunch of probably really inefficient math because the math library doesnt know how adding works.
	if (GetAsyncKeyState('W') & 0x8000) { eye = DirectX::XMVectorAdd(eye, DirectX::XMVectorScale(forward, delt * 3.f)); }
	if (GetAsyncKeyState('S') & 0x8000) { eye = DirectX::XMVectorSubtract(eye, DirectX::XMVectorScale(forward, delt * 3.f)); }
	if (GetAsyncKeyState('A') & 0x8000)
	{
		eye = DirectX::XMVectorSubtract(eye, DirectX::XMVectorScale(DirectX::XMVector3Cross(up, forward), delt * 3.f));
	}
	if (GetAsyncKeyState('D') & 0x8000) { eye = DirectX::XMVectorAdd(eye, DirectX::XMVectorScale(DirectX::XMVector3Cross(up, forward), delt * 3.f)); }

	//Go up and down with q and e because I'm a bad person and no one can use my key mappings
	if (GetAsyncKeyState('Q') & 0x8000) { eye = DirectX::XMVectorAdd(eye, DirectX::XMVectorScale(up, delt * 3.f)); }
	if (GetAsyncKeyState('E') & 0x8000) { eye = DirectX::XMVectorSubtract(eye, DirectX::XMVectorScale(up, delt * 3.f)); }

	//re-store everything back into the storage floats (and do a bit more math)
	DirectX::XMStoreFloat4x4(&m_mViewMat, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookToLH(eye, forward, up)));
	DirectX::XMStoreFloat3(&m_vPos, eye);
}

void Camera::Rotate(float a_fX, float a_fY, unsigned int width, unsigned int height)
{
	//a_fX is change in cursor screen position (say from 10 to 30)
	//xRot is the current angle of rotation along that axis
	//deltX represents a change of angle by a scaled amount of the distance that the cursor moved on that angle
	//Then clamp

	//Test by increment: 
	/*
	if (a_fX > 0) { m_fYRot += .003f; }
	if (a_fY > 0) { m_fXRot += .003f; }
	if (a_fX < 0) { m_fYRot -= .003f; }
	if (a_fY < 0) { m_fXRot -= .003f; }
	*/

	int trueWidth = width;
	int trueHeight = height;

	//Approach B: Inhouse (expensive) pull
	POINT cursor;
	GetCursorPos(&cursor);
	m_fYRot += .0003f * (cursor.x - trueWidth);
	m_fXRot += .0003f * (cursor.y - trueHeight);

	SetCursorPos(trueWidth, trueHeight);


	//This sort of works. Kind of. It works enough. Whatever, you can zip around the screen and look at my octogons, isn't that all that really matters?
	if (m_fXRot > DirectX::XMConvertToRadians(90))
	{
		m_fXRot = DirectX::XMConvertToRadians(90);
	}

	if (m_fXRot <  DirectX::XMConvertToRadians(-270))
	{
		m_fXRot = DirectX::XMConvertToRadians(-270);
	}

	//	if (m_fXRot > 360) { m_fXRot = (m_fXRot - 360); }
	//	if (m_fXRot < 0) { m_fXRot = (360 + m_fXRot); }

}

DirectX::XMFLOAT4X4 Camera::GetViewMat()
{
	return m_mViewMat;
}

DirectX::XMFLOAT4X4 Camera::GetProjMat()
{
	return m_mProjMat;
}

void Camera::SetProjection(unsigned int a_fHeight, unsigned int a_fWidth)
{
	DirectX::XMMATRIX P = DirectX::XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)a_fWidth / a_fHeight,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&m_mProjMat, XMMatrixTranspose(P)); // Transpose for HLSL!
}