#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <unordered_map>
#include <memory>
#include "../Utilities/Texture.h"
class DescriptorHeapBuilder
{
public:
    void Load(
        Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> * srvDescriptorHeap,
        std::unordered_map<std::string, std::unique_ptr<Texture>>* textures,
        UINT cbvSrvDescriptorSize,
        UINT* skyHeapIndex
    );

private:
};

