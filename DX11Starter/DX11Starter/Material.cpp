#include "Material.h"



Material::Material(SimpleVertexShader* vertex,
SimplePixelShader* pixel)
{
	vertexShader = vertex;
	pixelShader = pixel;
}


Material::~Material()
{
	vertexShader = nullptr;
	pixelShader = nullptr;
}

SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}

