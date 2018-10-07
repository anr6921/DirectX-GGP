#include "Material.h"



Material::Material(SimpleVertexShader* vertex,
SimplePixelShader* pixel, ID3D11ShaderResourceView* srvBoi, ID3D11SamplerState* smplr)
{
	vertexShader = vertex;
	pixelShader = pixel;
	SRV = srvBoi;
	sampler = smplr;
}


Material::~Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
	SRV = nullptr;
	sampler = nullptr;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}

ID3D11ShaderResourceView* Material::GetSRV() 
{ 
	return SRV; 
}

ID3D11SamplerState* Material::GetSamplerState() 
{ 
	return sampler; 
}

