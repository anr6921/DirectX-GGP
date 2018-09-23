#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"

using namespace DirectX;


class Camera
{
public:
	Camera();
	~Camera();

	DirectX::XMFLOAT4X4 GetViewMatrix();

	void SetViewMatrix(DirectX::XMFLOAT4X4 matrix);

	DirectX::XMFLOAT4X4 GetProjectionMatrix();

	void Update(float deltaTime);

	void rotateMousePosition(float mouseX, float mouseY);

	void updateProjectionMatrix(float width, float height);


private:
	DirectX::XMFLOAT4X4 viewMatrix; // viewer of the scene
	DirectX::XMFLOAT4X4 projectionMatrix; // map view back to a 2D scene

	// fields to track LOOK TO matrix (viewMatrix)
	DirectX::XMFLOAT3 position; // camera position
	DirectX::XMFLOAT3 direction; // camera direction
	float rotX; // rotation around the X axis
	float rotY; // rotation around the Y axis

};

