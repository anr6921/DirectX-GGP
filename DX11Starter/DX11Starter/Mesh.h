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
	int GetIndexCount();
	
private:
	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// how many indices are in the mesh's index buffer - used when drawing
	int bufferIndices;

	void SetBuffers(Vertex * vertices, int numVertices, UINT* indices, int numIndices, ID3D11Device * device);
};

