#include "../../DirectXing.h"

void DirectXing::DrawSceneToShadowMapInstructions()
{
    if (mUseShadowMap) {
        mCommandList->RSSetViewports(1, &mShadowMap->Viewport());
        mCommandList->RSSetScissorRects(1, &mShadowMap->ScissorRect());

        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mShadowMap->Resource(),
            D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE));

        UINT passCBByteSize = DirectXUtilities::CalcConstantBufferByteSize(sizeof(PassConstants));

        mCommandList->ClearDepthStencilView(mShadowMap->Dsv(),
            D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

        mCommandList->OMSetRenderTargets(0, nullptr, false, &mShadowMap->Dsv());

        auto passCB = mCurrFrameResource->PassCB->Resource();
        D3D12_GPU_VIRTUAL_ADDRESS passCBAddress = passCB->GetGPUVirtualAddress() + 1 * passCBByteSize;
        mCommandList->SetGraphicsRootConstantBufferView(1, passCBAddress);

        mCommandList->SetPipelineState(mPSOs["shadow_opaque"].Get());

        DrawRenderItemsInstructions(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Opaque]);
        DrawAddableRenderItemsInstructions(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Addable]);
        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mShadowMap->Resource(),
            D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));
    }
    else {
        mCommandList->ClearDepthStencilView(mShadowMap->Dsv(),
            D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
    }
   
}