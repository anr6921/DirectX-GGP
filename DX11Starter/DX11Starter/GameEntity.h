#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"

class GameEntity
{
public:
	GameEntity(Mesh* mesh);
	~GameEntity();

	// Accessors
	Mesh* GetMesh();
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	void SetWorldMatrix(DirectX::XMFLOAT4X4 matrix);
	DirectX::XMFLOAT3 GetPosition();
	void SetPosition(DirectX::XMFLOAT3 pos);
	DirectX::XMFLOAT3 GetRotation();
	void SetRotation(DirectX::XMFLOAT3 rot);
	DirectX::XMFLOAT3 GetScale();
	void SetScale(DirectX::XMFLOAT3 scl);

	// Move Entity
	void Transform(DirectX::XMMATRIX scl, DirectX::XMMATRIX rot, DirectX::XMMATRIX trans);

private:
	DirectX::XMFLOAT4X4 worldMatrix; // represents entities current position, rotation, and scale
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	Mesh* meshyboi;
};


