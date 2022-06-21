#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <unordered_map>
#include <memory>
#include "../Utilities/Texture.h"
#include "ShadowMap.h"
class DescriptorHeapBuilder
{
public:
    void Load(
        Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> * srvDescriptorHeap, 
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap, 
        std::unique_ptr<ShadowMap> * shadowMap, CD3DX12_GPU_DESCRIPTOR_HANDLE * nullSrv,
        std::unordered_map<std::string, std::unique_ptr<Texture>>* textures, 
        UINT cbvSrvDescriptorSize, UINT dsvDescriptorSize, UINT cbvSrvUavDescriptorSize, 
        UINT* skyHeapIndex, UINT* shadowMapHeapIndex, UINT* nullCubeSrvIndex, UINT* nullTexSrvIndex
    );

private:
};

