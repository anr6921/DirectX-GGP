#include "GameEntity.h"

using namespace DirectX;

GameEntity::GameEntity(Mesh* mesh)
{
	meshyboi = mesh; 
	position = DirectX::XMFLOAT3(0.0f,0.0f,0.0f);
	rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

}

GameEntity::~GameEntity()
{
	meshyboi = nullptr;
}

// Matrix accessors
DirectX::XMFLOAT4X4 GameEntity::GetWorldMatrix()
{
	return worldMatrix;
}

void GameEntity::SetWorldMatrix(DirectX::XMFLOAT4X4 matrix)
{
	worldMatrix = matrix;
}

// Position accessors
DirectX::XMFLOAT3 GameEntity::GetPosition()
{
	return position;
}

void GameEntity::SetPosition(DirectX::XMFLOAT3 pos)
{
	position = pos;
}

// Rotation accessors
DirectX::XMFLOAT3 GameEntity::GetRotation()
{
	return rotation;
}

void GameEntity::SetRotation(DirectX::XMFLOAT3 rot)
{
	rotation = rot;
}

// Scale accessors
DirectX::XMFLOAT3 GameEntity::GetScale()
{
	return scale;
}

void GameEntity::SetScale(DirectX::XMFLOAT3 scl)
{
	scale = scl;
}

// Move methods
void GameEntity::MoveRelative(float x, float y, float z)
{
	/*
	// rotate desired movement by our rotation
	XMVECTOR dir = XMVector3Rotate(
		XMVectorSet(x, y, z, 0),
		XMLoadFloat4()); //quaternion
	)*/
}

void GameEntity::MoveAbsolute(float x, float y, float z)
{
	// currentPosition is an XMFLOAT3
	position.x += x;
	position.y += y;
	position.z += z;
}