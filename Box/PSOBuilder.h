#pragma once
#include <unordered_map>
#include <wrl.h>
#include <d3d12.h>
#include <memory>
#include "../Utilities/MathHelper.h"

class PSOBuilder
{
public:
	void Load (Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>> *psos,
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout,
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature,
		std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> shaders, 
		DXGI_FORMAT backBufferFormat, bool m4xMsaaState, UINT m4xMsaaQuality,
		DXGI_FORMAT depthStencilFormat);
private:
};

