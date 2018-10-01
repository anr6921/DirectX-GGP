


// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	//float4 color		: COLOR;        // RGBA color
	float3 normal		: NORMAL;
	float2 uv			: TEXCOORD;
};

struct DirectionalLight
{
	float4 AmbientColor;
	float4 DiffuseColor;
	float3 Direction;
};

// Constant buffer for external data 
// (probably light-related for the pixel shader)
cbuffer ExternalData : register(b0)
{
	// Properties of the light
	DirectionalLight light;

	// The camera
	//float3 cameraPosition;

	// Material properties
	//float shininess;
}

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	// Just return the input color
	// - This color (like most values passing through the rasterizer) is 
	//   interpolated for each pixel between the corresponding vertices 
	//   of the triangle we're rendering
	//return input.color;

	// re-normalize normals 
	input.normal = normalize(input.normal);
//return float4(input.normal, 1); // temporary line
//return light.DiffuseColor;

	// LIGHT CALCULATIONS

	// Direction to the camera from the pixel
		// We'll need this for specular calc below
	float3 dirToLight = normalize(-light.Direction);

	// --- DIFFUSE (Lambert) --------------------
	// Basic diffuse (Lambert) lighting calc
	// Ensure we're using the direction TO the light
	float NdotL = saturate( dot(input.normal, dirToLight));

	// --- SPECULAR (Blinn Phong) --------------------
	// Calculate “half-way” vector between the light vector
	// and view vector (direction from surface to camera)
	//float3 h = normalize(-lightDirection + dirToCamera);

	// Calculate the cosine of the normal and halfway vector
	// Saturate() ensures it’s between 0 and 1
	//float NdotH = saturate(dot(input.normal, h));

	// define an ambient light color
	//float3 ambient = float3(0.15f, 0.25f, 0.35f);

	// Raise the ratio to a power equal to some// “shininess” factor – try a number between 1 and 64
	//float specAmt = pow(NdotH, shininess);
	//float3 specColor = float3(specAmt, specAmt, specAmt);

	//return float4(ambient, 0);
	// --- FINAL COLOR ----------------------------
	return float4(
		light.AmbientColor +
		light.DiffuseColor * NdotL);
}