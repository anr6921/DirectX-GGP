#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include <d3d11.h>
#include "Vertex.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	ID3D11Buffer * GetVertexBuffer();
	ID3D11Buffer * GetIndexBuffer();
	int GetIndexCount();
private:
	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// how many indices are in the mesh's index buffer - used when drawing
	int bufferIndices;
};

