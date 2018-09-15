#include "GameEntity.h"

using namespace DirectX;

GameEntity::GameEntity(Mesh* mesh)
{
	meshyboi = mesh; 
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	scale = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

}

GameEntity::~GameEntity()
{
	meshyboi = nullptr;
}

// Mesh accessors
/*
ID3D11Buffer* GameEntity::GetVertexBuffer()
{
	return meshyboi->GetVertexBuffer();
}

ID3D11Buffer* GameEntity::GetIndexBuffer()
{
	return meshyboi->GetVertexBuffer();
}

UINT GameEntity::GetIndexCount()
{
	return meshyboi->GetIndexCount();
}*/
Mesh* GameEntity::GetMesh()
{
	return meshyboi;
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

// Trasformation matrix
void GameEntity::Transform(DirectX::XMMATRIX worldMat)
{
	/*
	// Load in variables to be changed
	XMVECTOR trans = XMLoadFloat3(&position);
	XMVECTOR rot = XMLoadFloat3(&rotation);
	XMVECTOR scl = XMLoadFloat3(&scale);

	XMMATRIX worldMat = XMLoadFloat4x4(&worldMatrix);
	XMMATRIX translation = XMMatrixTranslation(10,0,0);

	// Calculate
	//XMMATRIX world = scl * rot * trans;
	worldMat = XMMatrixMultiply(worldMat, translation);*/

	// Store results
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(worldMat));
	
	//vertexShader->SetMatrix4x4("world", entity1->GetWorldMatrix);
	//printf("world: ", worldMatrix);
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