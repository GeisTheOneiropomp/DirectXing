#pragma once
#include <string>
#include <wrl.h>
#include <d3d12.h>
class Texture
{

public:

    Microsoft::WRL::ComPtr<ID3D12Resource> Resource = nullptr;
    Microsoft::WRL::ComPtr<ID3D12Resource> UploadHeap = nullptr;

    Texture(std::string Name, std::wstring Filename);
    Microsoft::WRL::ComPtr<ID3D12Resource> &GetResource();
    Microsoft::WRL::ComPtr<ID3D12Resource> &GetUploadHeap();

    std::string Name;
    std::wstring Filename;

};