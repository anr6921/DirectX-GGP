#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Camera.h"
#include <DirectXMath.h>

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexBuffer = 0;
	indexBuffer = 0;
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;
	
	// delete meshy boys
	delete mesh1;
	delete mesh2;
	delete mesh3;

	// delete game entities
	delete entity1;
	delete entity2;
	delete entity3;
	delete entity4;
	delete entity5;
	delete entity6;
	delete entity7;

	// delete camera
	delete camera;

	// delete materials
	delete material1;
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();
	camera = new Camera();


	// Camera projection matrix
	camera->updateProjectionMatrix(width, height);

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");

	material1 = new Material(vertexShader, pixelShader);
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	DirectX::XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	DirectX::XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices1[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), // position
		XMFLOAT3(+0.0f, +0.0f, +1.0f), // normal
		XMFLOAT2(0.0f,0.0f)}, // UV
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
	};

	Vertex vertices2[] =
	{
		{ XMFLOAT3(+1.0f, +2.0f, +1.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+2.5f, +0.0f, +1.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-0.5f, +0.0f, +1.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
	};

	Vertex vertices3[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), XMFLOAT3(+0.0f, +0.0f, +1.0f), XMFLOAT2(0.0f,0.0f) },
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	// - But just to see how it's done...
	UINT indices[] = { 0, 1, 2 };

	mesh1 = new Mesh("cube.obj", device);
	mesh2 = new Mesh(vertices2, 3, indices, 3, device);
	mesh3 = new Mesh(vertices3, 3, indices, 3, device);


	entity1 = new GameEntity(mesh3, material1);
	entity2 = new GameEntity(mesh2, material1);
	entity3 = new GameEntity(mesh3, material1);
	entity4 = new GameEntity(mesh3, material1);
	entity5 = new GameEntity(mesh3, material1);
	entity6 = new GameEntity(mesh3, material1);
	entity7 = new GameEntity(mesh1, material1);
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	DirectX::XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!

	// Camera class projection matrix
	camera->updateProjectionMatrix(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	// Update positions

	// Camera 
	camera->Update(deltaTime);

	
	// Entity 1
	float sinTime = (sin(totalTime));
	entity1->Transform(
		XMMatrixScaling(sinTime, sinTime, sinTime),
		XMMatrixRotationX(totalTime),
		XMMatrixTranslation(1, 0, 0));

	// Entity 2
	float cosTime = (cos(totalTime));
	entity2->Transform(
		XMMatrixScaling(1, 1, 1),
		XMMatrixRotationX(0),
		XMMatrixTranslation(0, 0, 0));

	// Entity 3
	entity3->Transform(
		XMMatrixScaling(1, 0.5, 1),
		XMMatrixRotationY(totalTime),
		XMMatrixTranslation(-2, 0, 0));

	// Entity 4
	entity4->Transform(
		XMMatrixScaling(0.5, 0.25, 0.5),
		XMMatrixRotationZ(totalTime),
		XMMatrixTranslation(-2, -1, 0));

	// Entity 5
	entity5->Transform(
		XMMatrixScaling(0.5, 0.25, 0.5),
		XMMatrixRotationZ(totalTime),
		XMMatrixTranslation(2, -1* totalTime, -0.5));

	// Entity 6
	entity6->Transform(
		XMMatrixScaling(0.5, 0.5, 0.5),
		XMMatrixRotationZ(totalTime),
		XMMatrixTranslation(-1, -1, -0.5*totalTime));

	// Entity 6
	entity7->Transform(
		XMMatrixScaling(0.5, 0.5, 0.5),
		XMMatrixRotationZ(totalTime),
		XMMatrixTranslation(2, 1, 0));
	
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	//vertexShader->SetMatrix4x4("world", worldMatrix);
	//vertexShader->SetMatrix4x4("view", viewMatrix);
	//vertexShader->SetMatrix4x4("projection", projectionMatrix);

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	//vertexShader->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	//vertexShader->SetShader();
	//pixelShader->SetShader();

	/*
	// Set buffers in the input assembler
	//  - Do this ONCE PER OBJECT you're drawing, since each object might
	//    have different geometry.
	
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	*/
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Entity 1 - Pass world matrix into shader
	entity1->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 1
	Mesh* meshEntity1 = entity1->GetMesh();
	ID3D11Buffer* vBuffer1 = meshEntity1->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer1, &stride, &offset);
	context->IASetIndexBuffer(meshEntity1->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity1->GetIndexCount(),
		0,
		0);

	// Entity 2 - pass into shader
	// Pass world matrix into shader
	entity2->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 2
	Mesh* meshEntity2 = entity2->GetMesh();
	ID3D11Buffer* vBuffer2 = meshEntity2->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer2, &stride, &offset);
	context->IASetIndexBuffer(meshEntity2->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity2->GetIndexCount(),
		0,
		0);

	// Entity 3 - pass into shader
	// Pass world matrix into shader
	entity3->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 3
	Mesh* meshEntity3 = entity3->GetMesh();
	ID3D11Buffer* vBuffer3 = meshEntity3->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer3, &stride, &offset);
	context->IASetIndexBuffer(meshEntity3->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity3->GetIndexCount(),
		0,
		0);

	// Entity 4 - pass into shader
	// Pass world matrix into shader
	entity4->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 4
	Mesh* meshEntity4 = entity4->GetMesh();
	ID3D11Buffer* vBuffer4 = meshEntity4->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer4, &stride, &offset);
	context->IASetIndexBuffer(meshEntity4->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity4->GetIndexCount(),
		0,
		0);

	// Entity 5 - pass into shader
	// Pass world matrix into shader
	entity5->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 5
	Mesh* meshEntity5 = entity5->GetMesh();
	ID3D11Buffer* vBuffer5 = meshEntity5->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer5, &stride, &offset);
	context->IASetIndexBuffer(meshEntity5->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity5->GetIndexCount(),
		0,
		0);

	// Entity 6 - pass into shader
	// Pass world matrix into shader
	entity6->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 5
	Mesh* meshEntity6 = entity6->GetMesh();
	ID3D11Buffer* vBuffer6 = meshEntity6->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer6, &stride, &offset);
	context->IASetIndexBuffer(meshEntity6->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity6->GetIndexCount(),
		0,
		0);

	// Entity 7 - pass into shader
	// Pass world matrix into shader
	entity7->PrepareMaterial(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	// Draw Entity 7
	Mesh* meshEntity7 = entity7->GetMesh();
	ID3D11Buffer* vBuffer7 = meshEntity7->GetVertexBuffer();
	context->IASetVertexBuffers(0, 1, &vBuffer7, &stride, &offset);
	//context->IASetIndexBuffer(meshEntity7->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->DrawIndexed(
		meshEntity7->GetIndexCount(),
		0,
		0);



	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	if (buttonState & 0x0002)
	{
		float changeX = prevMousePos.x - x;
		float changeY = prevMousePos.y - y;
		camera->rotateMousePosition(changeX, changeY);
	}

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion