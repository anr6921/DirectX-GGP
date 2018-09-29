#include "Camera.h"

using namespace DirectX;

Camera::Camera()
{
	rotX = 0.0f;
	rotY = 0.0f;
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
	XMMATRIX rot = XMMatrixTranspose(XMMatrixRotationQuaternion(forward));

	// Unit Vector Z
	XMVECTOR unitZ = XMVectorSet(0, 0, 1, 0);
	// apply resulting matrix to default forward vector on Z axis
	XMVECTOR dir = XMVector3Transform(unitZ, rot);
	//XMVECTOR dir = XMVectorSet(0, 0, 1, 0); // delete this before turning in

	XMVECTOR pos = DirectX::XMLoadFloat3(&position);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	// left vectors
	XMVECTOR left = XMVector3Cross(dir, up);

	// Key movement
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

void Camera::rotateMousePosition(float mouseX, float mouseY)
{
	rotX += mouseY*0.005;
	rotY += mouseX*0.005;
}

void Camera::updateProjectionMatrix(float width, float height)
{
	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	DirectX::XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}
