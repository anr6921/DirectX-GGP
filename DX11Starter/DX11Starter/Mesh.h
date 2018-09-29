#pragma once

#include "Vertex.h"
#include <d3d11.h>

class Mesh
{
public:
	Mesh(char* objFile, ID3D11Device* device);
	Mesh(Vertex* vertices, UINT numVertices, UINT* indices, UINT numIndices, ID3D11Device* device);
	~Mesh();
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	UINT GetIndexCount();
	void SetBuffers(Vertex * vertices, UINT numVertices, UINT * indices, UINT numIndices, ID3D11Device * device);
private:
	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// how many indices are in the mesh's index buffer - used when drawing
	UINT bufferIndices;
};

