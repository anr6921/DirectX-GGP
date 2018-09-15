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

	/*
	ID3D11Buffer * GetVertexBuffer();

	ID3D11Buffer * GetIndexBuffer();

	UINT GetIndexCount();*/

	Mesh* GetMesh();

	//Accessors
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	void SetWorldMatrix(DirectX::XMFLOAT4X4 matrix);
	DirectX::XMFLOAT3 GetPosition();
	void SetPosition(DirectX::XMFLOAT3 pos);
	DirectX::XMFLOAT3 GetRotation();
	void SetRotation(DirectX::XMFLOAT3 rot);
	DirectX::XMFLOAT3 GetScale();
	void SetScale(DirectX::XMFLOAT3 scl);

	void Transform(DirectX::XMMATRIX worldMat);

	void MoveRelative(float x, float y, float z);

	//Move methods
	void MoveAbsolute(float x, float y, float z);

private:
	DirectX::XMFLOAT4X4 worldMatrix; // represents entities current position, rotation, and scale
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	Mesh* meshyboi;
};


