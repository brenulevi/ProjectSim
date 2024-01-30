#include "Cube.h"

#include "AllBindables.h"

#include "Mouse.h"
#include "Keyboard.h"

Cube::Cube(Graphics& gfx, float xSpeed, float ySpeed, float zSpeed)
	:
	xView(0.0f),
	yView(0.0f),
	zView(0.0f),
	xMove(0.0f),
	yMove(0.0f),
	zMove(0.0f),
	xSpeed(xSpeed),
	ySpeed(ySpeed),
	zSpeed(zSpeed)
{
	struct VERTEX
	{
		float x, y, z;
	};

	const std::vector<VERTEX> vertices =
	{
		{ -1.0f,-1.0f,-1.0f },
		{ 1.0f,-1.0f,-1.0f },
		{ -1.0f,1.0f,-1.0f },
		{ 1.0f,1.0f,-1.0f },
		{ -1.0f,-1.0f,1.0f },
		{ 1.0f,-1.0f,1.0f },
		{ -1.0f,1.0f,1.0f },
		{ 1.0f,1.0f,1.0f },
	};
	AddBind(std::make_unique<VertexBuffer>(gfx, vertices));

	auto vso = std::make_unique<VertexShader>(gfx, L"Shader/VertexShader.hlsl");
	auto vsbc = vso->getByteCode();

	vso->Bind(gfx);

	auto pso = std::make_unique<PixelShader>(gfx, L"Shader/PixelShader.hlsl");
	pso->Bind(gfx);

	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};
	AddIndexBuffer(std::make_unique<IndexBuffer>(gfx, indices));

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};

	const ConstantBuffer2 cb2 =
	{
		{
			{ 1.0f,0.0f,1.0f },
			{ 1.0f,0.0f,0.0f },
			{ 0.0f,1.0f,0.0f },
			{ 0.0f,0.0f,1.0f },
			{ 1.0f,1.0f,0.0f },
			{ 0.0f,1.0f,1.0f },
		}
	};
	AddBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(gfx, cb2));

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
	{
		{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	AddBind(std::make_unique<InputLayout>(gfx, ied, vsbc));

	AddBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	AddBind(std::make_unique<TransformConstantBuffer>(gfx, *this));

}

void Cube::Update(float deltaTime)
{
	xView = (Mouse::GetMouseX() / 400.0f - 1.0f) * 5.0f;
	yView = (-Mouse::GetMouseY() / 300.0f + 1.0f) * 5.0f;

	if (Keyboard::GetKey('W'))
		zMove += xSpeed * deltaTime;
	if (Keyboard::GetKey('S'))
		zMove -= xSpeed * deltaTime;

	if (Keyboard::GetKey('D'))
		xMove += ySpeed * deltaTime;
	if (Keyboard::GetKey('A'))
		xMove -= ySpeed * deltaTime;

	if (Keyboard::GetKey('R'))
		yMove += ySpeed * deltaTime;
	if (Keyboard::GetKey('F'))
		yMove -= ySpeed * deltaTime;
}

DX::XMMATRIX Cube::GetTransformMatrix()
{
	return	DX::XMMatrixRotationZ(xView) *
		DX::XMMatrixRotationX(yView) *
		DX::XMMatrixTranslation(xMove, yMove, zMove) *
		DX::XMMatrixTranslation(0.0f, 0.0f, 5.0f);
}