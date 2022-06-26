#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <unordered_map>
#include <memory>

class ShadersLoader
{
public:
    void Load(
        std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> * shaders,
        std::vector<D3D12_INPUT_ELEMENT_DESC> * inputLayout
    );

};

