#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>

class Material
{
public:
	Material(SimpleVertexShader* vertex,
		SimplePixelShader* pixel, ID3D11ShaderResourceView* srvBoi, ID3D11SamplerState* smplr);
	~Material();

	SimpleVertexShader * GetVertexShader();

	SimplePixelShader * GetPixelShader();

	ID3D11ShaderResourceView* GetSRV();
	ID3D11SamplerState* GetSamplerState();

	
private:
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
	ID3D11ShaderResourceView* SRV;
	ID3D11SamplerState* sampler;
};


