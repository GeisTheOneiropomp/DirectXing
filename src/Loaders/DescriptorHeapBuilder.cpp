#include "../DirectXing.h"
#include "../Utilities/DirectXUtilities.h"

void DirectXing::BuildDescriptorHeap()
{

    D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
    srvHeapDesc.NumDescriptors = 18;
    srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

    auto brickDiffuseTex = mTextures["bricksDiffuseMap"]->GetResource();
    auto brickNormalTex = mTextures["bricksNormalMap"]->GetResource();
    auto tileDiffuseMap = mTextures["tileDiffuseMap"]->GetResource();
    auto tileNormalMap = mTextures["tileNormalMap"]->GetResource();
    auto defaultDiffuseMap = mTextures["defaultDiffuseMap"]->GetResource();
    auto defaultNormalMap = mTextures["defaultNormalMap"]->GetResource();
    auto skyTex = mTextures["skyCubeMap"]->GetResource();

    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

    srvDesc.Format = brickDiffuseTex->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = brickDiffuseTex->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(brickDiffuseTex.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.Format = brickNormalTex->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = brickNormalTex->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(brickNormalTex.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.Format = tileDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileDiffuseMap->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(tileDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.Format = tileNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = tileNormalMap->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(tileNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.Format = defaultDiffuseMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultDiffuseMap->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(defaultDiffuseMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.Format = defaultNormalMap->GetDesc().Format;
    srvDesc.Texture2D.MipLevels = defaultNormalMap->GetDesc().MipLevels;
    md3dDevice->CreateShaderResourceView(defaultNormalMap.Get(), &srvDesc, hDescriptor);
    hDescriptor.Offset(1, mCbvSrvUavDescriptorSize);

    // next descriptor

    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
    srvDesc.TextureCube.MostDetailedMip = 0;
    srvDesc.TextureCube.MipLevels = skyTex->GetDesc().MipLevels;
    srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
    srvDesc.Format = skyTex->GetDesc().Format;
    md3dDevice->CreateShaderResourceView(skyTex.Get(), &srvDesc, hDescriptor);

    //TODO:: Fix magic constant;
    mSkyTexHeapIndex = 6;
    mShadowMapHeapIndex = mSkyTexHeapIndex + 1;
    mSsaoHeapIndexStart = mShadowMapHeapIndex + 1;
    mSsaoAmbientMapIndex = mSsaoHeapIndexStart + 3;
    mNullCubeSrvIndex = mSsaoHeapIndexStart + 5;
    mNullTexSrvIndex1 = mNullCubeSrvIndex + 1;
    mNullTexSrvIndex2 = mNullTexSrvIndex1 + 1;

    auto nullSrv = GetCpuSrv(mNullCubeSrvIndex);
    mNullSrv = GetGpuSrv(mNullCubeSrvIndex);
    
    md3dDevice->CreateShaderResourceView(nullptr, &srvDesc, nullSrv);
    nullSrv.Offset(1, mCbvSrvUavDescriptorSize);

    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
    md3dDevice->CreateShaderResourceView(nullptr, &srvDesc, nullSrv);

    nullSrv.Offset(1, mCbvSrvUavDescriptorSize);
    md3dDevice->CreateShaderResourceView(nullptr, &srvDesc, nullSrv);

    mShadowMap->BuildDescriptors(
        GetCpuSrv(mShadowMapHeapIndex),
        GetGpuSrv(mShadowMapHeapIndex),
        GetDsv(1));

    mSSAmbientOcclusion->BuildDescriptors(
        mDepthStencilBuffer.Get(),
        GetCpuSrv(mSsaoHeapIndexStart),
        GetGpuSrv(mSsaoHeapIndexStart),
        GetRtv(SwapChainBufferCount),
        mCbvSrvUavDescriptorSize,
        mRtvDescriptorSize);
}

CD3DX12_CPU_DESCRIPTOR_HANDLE DirectXing::GetCpuSrv(int index) const
{
    auto srv = CD3DX12_CPU_DESCRIPTOR_HANDLE(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());
    srv.Offset(index, mCbvSrvUavDescriptorSize);
    return srv;
}

CD3DX12_GPU_DESCRIPTOR_HANDLE DirectXing::GetGpuSrv(int index)const
{
    auto srv = CD3DX12_GPU_DESCRIPTOR_HANDLE(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
    srv.Offset(index, mCbvSrvUavDescriptorSize);
    return srv;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE DirectXing::GetDsv(int index)const
{
    auto dsv = CD3DX12_CPU_DESCRIPTOR_HANDLE(mDsvHeap->GetCPUDescriptorHandleForHeapStart());
    dsv.Offset(index, mDsvDescriptorSize);
    return dsv;
}

CD3DX12_CPU_DESCRIPTOR_HANDLE DirectXing::GetRtv(int index)const
{
    auto rtv = CD3DX12_CPU_DESCRIPTOR_HANDLE(mRtvHeap->GetCPUDescriptorHandleForHeapStart());
    rtv.Offset(index, mRtvDescriptorSize);
    return rtv;
}
