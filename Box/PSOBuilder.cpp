#include "PSOBuilder.h"
#include "../Utilities/d3dx12.h"
#include "../Utilities/d3dUtil.h"

void PSOBuilder::Load(Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice, 
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList, 
    std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D12PipelineState>> *psos,
    std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout,
    Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature,
    std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> shaders,
    DXGI_FORMAT backBufferFormat, bool fourxMsaaState, UINT fourxMsaaQuality,
    DXGI_FORMAT depthStencilFormat
    )
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
    ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    psoDesc.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
    psoDesc.pRootSignature = rootSignature.Get();
    psoDesc.VS =
    {
        reinterpret_cast<BYTE*>(shaders["standardVS"]->GetBufferPointer()),
        shaders["standardVS"]->GetBufferSize()
    };
    psoDesc.PS =
    {
        reinterpret_cast<BYTE*>(shaders["opaquePS"]->GetBufferPointer()),
        shaders["opaquePS"]->GetBufferSize()
    };
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = backBufferFormat;
    psoDesc.SampleDesc.Count = fourxMsaaState ? 4 : 1;
    psoDesc.SampleDesc.Quality = fourxMsaaState ? (fourxMsaaQuality - 1) : 0;
    psoDesc.DSVFormat = depthStencilFormat;
    auto opaquePSO = (*psos)["opaque"];
    ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&(*psos)["opaque"])));

    //
    // PSO for sky.
    //
    D3D12_GRAPHICS_PIPELINE_STATE_DESC skyPsoDesc = psoDesc;

    // The camera is inside the sky sphere, so just turn off culling.
    skyPsoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

    // Make sure the depth function is LESS_EQUAL and not just LESS.  
    // Otherwise, the normalized depth values at z = 1 (NDC) will 
    // fail the depth test if the depth buffer was cleared to 1.
    skyPsoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    skyPsoDesc.pRootSignature = rootSignature.Get();
    skyPsoDesc.VS =
    {
        reinterpret_cast<BYTE*>(shaders["skyVS"]->GetBufferPointer()),
        shaders["skyVS"]->GetBufferSize()
    };
    skyPsoDesc.PS =
    {
        reinterpret_cast<BYTE*>(shaders["skyPS"]->GetBufferPointer()),
        shaders["skyPS"]->GetBufferSize()
    };
    auto skyPSO = (*psos)["sky"];
    ThrowIfFailed(d3dDevice->CreateGraphicsPipelineState(&skyPsoDesc, IID_PPV_ARGS(&(*psos)["sky"])));
}
