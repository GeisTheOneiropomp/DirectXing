#include "DescriptorHeapBuilder.h"
#include "../Utilities/d3dUtil.h"

void DescriptorHeapBuilder::Load(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, 
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> * srvDescriptorHeap, 
	std::unordered_map<std::string, std::unique_ptr<Texture>>* textures, 
	UINT cbvSrvDescriptorSize, UINT* skyHeapIndex)
{
    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 10;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    ThrowIfFailed(d3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&(*srvDescriptorHeap))));

    auto brickDiffuseTex = (*textures)["bricksDiffuseMap"]->GetResource();
    auto brickNormalTex = (*textures)["bricksNormalMap"]->GetResource();
    auto tileDiffuseMap = (*textures)["tileDiffuseMap"]->GetResource();
    auto tileNormalMap = (*textures)["tileNormalMap"]->GetResource();
    auto defaultDiffuseMap = (*textures)["defaultDiffuseMap"]->GetResource();
    auto defaultNormalMap = (*textures)["defaultNormalMap"]->GetResource();
    auto skyTex = (*textures)["skyCubeMap"]->GetResource();

    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor((*srvDescriptorHeap)->GetCPUDescriptorHandleForHeapStart());


    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

    srvDesc.Format = brickDiffuseTex->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = brickDiffuseTex->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(brickDiffuseTex.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    srvDesc.Format = brickNormalTex->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = brickNormalTex->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(brickNormalTex.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    srvDesc.Format = tileDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileDiffuseMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(tileDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    srvDesc.Format = tileNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileNormalMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(tileNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    srvDesc.Format = defaultDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultDiffuseMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(defaultDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    srvDesc.Format = defaultNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultNormalMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(defaultNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvDescriptorSize);

    // next descriptor

    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.TextureCube.MostDetailedMip = 0;
    srvDesc.TextureCube.MipLevels = skyTex->GetDesc().MipLevels;
    srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
    srvDesc.Format = skyTex->GetDesc().Format;
    d3dDevice->CreateShaderResourceView(skyTex.Get(), &srvDesc, hDescriptor);

    *skyHeapIndex = 6;
}
