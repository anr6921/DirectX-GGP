#include "Camera.h"

using namespace DirectX;

Camera::Camera()
{
	rotX = 1.0f;
	rotY = 1.0f;
	position = XMFLOAT3(0.f, 0.f, -5.f);
}


Camera::~Camera()
{
}

DirectX::XMFLOAT4X4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::SetViewMatrix(DirectX::XMFLOAT4X4 matrix)
{
	viewMatrix = matrix;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::Update(float deltaTime)
{
	// Create rotation matrix based on current X and Y rotation values
	XMVECTOR forward = XMQuaternionRotationRollPitchYaw(rotX, rotY, 0.0f);
	XMMATRIX rot = XMMatrixRotationQuaternion(forward);

	//XMMatrixRotationRollPitchYaw(rotX, rotY, 0.0f);
	//DirectX::XMVECTOR forward = XMQuaternionRotationRollPitchYaw(rotX, rotY, 0.0f);

	// Unit Vector Z
	XMVECTOR unitZ = XMVectorSet(0, 0, 1, 0);
	// apply resulting matrix to default forward vector on Z axis
	XMVECTOR dir = XMVector3Transform(unitZ, rot);
	//XMVECTOR dir = XMVectorSet(0, 0, 1, 0);

	XMVECTOR pos = DirectX::XMLoadFloat3(&position);
		//XMVectorSet(0, 0, -5, 0);
	//XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	// left vectors
	XMVECTOR left = XMVector3Cross(dir, up);

	if (GetAsyncKeyState('W') & 0x8000) // forwards
	{
		pos += dir * deltaTime;
		DirectX::XMStoreFloat3(&position, pos);
	}
	if (GetAsyncKeyState('S') & 0x8000) // backwards
	{
		pos -= dir * deltaTime;
		DirectX::XMStoreFloat3(&position, pos);
	}
	if (GetAsyncKeyState('A') & 0x8000) // strafe left
	{
		pos += left * deltaTime;
		DirectX::XMStoreFloat3(&position, pos);
	}
	if (GetAsyncKeyState('D') & 0x8000) // strafe right
	{
		pos -= left * deltaTime;
		DirectX::XMStoreFloat3(&position, pos);
	}
	if (GetAsyncKeyState('C') & 0x8000) // Move up y axis
	{
		position.y += deltaTime;
	}
	if (GetAsyncKeyState('X') & 0x8000) // move down y axis
	{
		position.y -= deltaTime;
	}
	
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)

	// store in view matrix
	DirectX::XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V));
}
