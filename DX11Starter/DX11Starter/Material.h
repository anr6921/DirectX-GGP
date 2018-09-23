#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

class Material
{
public:
	Material(SimpleVertexShader* vertex,
		SimplePixelShader* pixel);
	~Material();

	SimpleVertexShader * GetVertexShader();

	SimplePixelShader * GetPixelShader();
	
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};


