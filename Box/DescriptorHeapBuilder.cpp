#include "DescriptorHeapBuilder.h"
#include "../Utilities/d3dUtil.h"

void DescriptorHeapBuilder::Load(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>* srvDescriptorHeap, 
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvHeap,
    std::unique_ptr<ShadowMap>* shadowMap, CD3DX12_GPU_DESCRIPTOR_HANDLE* nullSrv,
    std::unordered_map<std::string, std::unique_ptr<Texture>>* textures,
    UINT cbvSrvDescriptorSize, UINT dsvDescriptorSize, UINT cbvSrvUavDescriptorSize,
    UINT* skyHeapIndex, UINT* shadowMapHeapIndex, UINT* nullCubeSrvIndex, UINT* nullTexSrvIndex)
{

    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 14;
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
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.Format = brickNormalTex->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = brickNormalTex->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(brickNormalTex.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.Format = tileDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileDiffuseMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(tileDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.Format = tileNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileNormalMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(tileNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.Format = defaultDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultDiffuseMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(defaultDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.Format = defaultNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultNormalMap->GetDesc().MipLevels;
    d3dDevice->CreateShaderResourceView(defaultNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, cbvSrvUavDescriptorSize);

    // next descriptor

    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.TextureCube.MostDetailedMip = 0;
    srvDesc.TextureCube.MipLevels = skyTex->GetDesc().MipLevels;
    srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
    srvDesc.Format = skyTex->GetDesc().Format;
    d3dDevice->CreateShaderResourceView(skyTex.Get(), &srvDesc, hDescriptor);

    //TODO:: Fix magic constant;
    *skyHeapIndex = 6;

    *shadowMapHeapIndex = (*skyHeapIndex) + 1;
    *nullCubeSrvIndex = (*shadowMapHeapIndex) + 1;
    *nullTexSrvIndex = (*nullCubeSrvIndex) + 1;

    auto srvCpuStart = (*srvDescriptorHeap)->GetCPUDescriptorHandleForHeapStart();
    auto srvGpuStart = (*srvDescriptorHeap)->GetGPUDescriptorHandleForHeapStart();
    auto dsvCpuStart = dsvHeap->GetCPUDescriptorHandleForHeapStart();

    auto cpuNullSrv = CD3DX12_CPU_DESCRIPTOR_HANDLE(srvCpuStart, *nullCubeSrvIndex, cbvSrvUavDescriptorSize);
    (*nullSrv) = CD3DX12_GPU_DESCRIPTOR_HANDLE(srvGpuStart, *nullCubeSrvIndex, cbvSrvUavDescriptorSize);

    d3dDevice->CreateShaderResourceView(nullptr, &srvDesc, cpuNullSrv);
    cpuNullSrv.Offset(1, cbvSrvUavDescriptorSize);

    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
    d3dDevice->CreateShaderResourceView(nullptr, &srvDesc, cpuNullSrv);

    (*shadowMap)->BuildDescriptors(
        CD3DX12_CPU_DESCRIPTOR_HANDLE(srvCpuStart, *shadowMapHeapIndex, cbvSrvUavDescriptorSize),
        CD3DX12_GPU_DESCRIPTOR_HANDLE(srvGpuStart, *shadowMapHeapIndex, cbvSrvUavDescriptorSize),
        CD3DX12_CPU_DESCRIPTOR_HANDLE(dsvCpuStart, 1, dsvDescriptorSize));
}
