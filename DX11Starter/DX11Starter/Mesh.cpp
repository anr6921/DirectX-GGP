#include "Mesh.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

Mesh::Mesh()
{
	bufferIndices = 0; // how many indices are in the mash's index buffer

	// Create some temporary variables to represent colors
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// array of Vertex objects
	Vertex vertices[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), green },
	};

	// int specifying number of indices in the index array
	int numVertices;

	// array of unsigned integers for indices
	UINT indices[] = { 0, 1, 2 };

	// num of indices in index array
	int numIndices;

	// point to device object used to create buffers
	ID3D11Device* createBuffer;

	vertexBuffer;
	indexBuffer;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	//device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	//device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
	
}

Mesh::~Mesh()
{
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{

}

ID3D11Buffer* Mesh::GetIndexBuffer()
{

}

int Mesh::GetIndexCount()
{

}

