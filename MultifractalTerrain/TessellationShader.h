// Light shader.h
// Basic single light shader setup

#ifndef _TESSELLATIONSHADER_H_
#define _TESSELLATIONSHADER_H_

#include "../DXFramework/BaseShader.h"
#include "../DXFramework/Camera.h"
#include "../DXFramework/Light.h"

using namespace std;
using namespace DirectX;

// 主要地形着色器的参数设置
class TessellationShader : public BaseShader
{
public:

	// 存储传递给着色器的过程参数
	struct MultifractalBufferType
	{
		float H; float lacunarity; float octaves; float offset; float gain; XMFLOAT3 padding;
	};

private:

	// 恒定缓冲区
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
	};

	// 着色器参数的输入缓冲区
	struct TessDistanceBufferType
	{
		float tessNear;
		float tessFar;
		XMFLOAT2 padding;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPos;
		float camPadding;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambient;
		XMFLOAT4 diffuse;
		XMFLOAT4 position;
	};

	struct LightBufferType2
	{
		XMFLOAT3 position;
		float padding;
	};



public:

	TessellationShader(ID3D11Device* device, HWND hwnd);
	~TessellationShader();

	//Tess中Shader参数设定
	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, 
								ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* snowTexture, ID3D11ShaderResourceView*depthMap,
								float tessDistNear, float tessDistFar, Camera* camera, Light* light, MultifractalBufferType multifractalData, bool fog);


	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);



private:

	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename);

private:

	// DX11 Attributes
	ID3D11Buffer* m_matrixBuffer;

	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11SamplerState* m_sampleState;

	ID3D11Buffer* m_TessDistanceBuffer;

	ID3D11Buffer* m_CameraBuffer;

	ID3D11Buffer* m_MoonlightBuffer;
	ID3D11Buffer* m_MoonlightBuffer2;

	ID3D11Buffer* m_MultifractalBuffer;

};

#endif