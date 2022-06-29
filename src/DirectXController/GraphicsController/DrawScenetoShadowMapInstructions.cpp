#include "../../DirectXing.h"

void DirectXing::DrawSceneToShadowMapInstructions()
{
    if (mUseShadowMap) {
        mCommandList->RSSetViewports(1, &mShadowMap->Viewport());
        mCommandList->RSSetScissorRects(1, &mShadowMap->ScissorRect());

        // Change to DEPTH_WRITE.
        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mShadowMap->Resource(),
            D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_DEPTH_WRITE));

        UINT passCBByteSize = DirectXUtilities::CalcConstantBufferByteSize(sizeof(PassConstants));

        // Clear the back buffer and depth buffer.
        mCommandList->ClearDepthStencilView(mShadowMap->Dsv(),
            D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

        // Set null render target because we are only going to draw to
        // depth buffer.  Setting a null render target will disable color writes.
        // Note the active PSO also must specify a render target count of 0.
        mCommandList->OMSetRenderTargets(0, nullptr, false, &mShadowMap->Dsv());

        // Bind the pass constant buffer for the shadow map pass.
        auto passCB = mCurrFrameResource->PassCB->Resource();
        D3D12_GPU_VIRTUAL_ADDRESS passCBAddress = passCB->GetGPUVirtualAddress() + 1 * passCBByteSize;
        mCommandList->SetGraphicsRootConstantBufferView(1, passCBAddress);

        mCommandList->SetPipelineState(mPSOs["shadow_opaque"].Get());

        DrawRenderItemsInstructions(mCommandList.Get(), mRitemLayer[(int)RenderLayer::Opaque]);

        // Change back to GENERIC_READ so we can read the texture in a shader.
        mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(mShadowMap->Resource(),
            D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_GENERIC_READ));
    }
    else {
        // Clear the back buffer and depth buffer.
        mCommandList->ClearDepthStencilView(mShadowMap->Dsv(),
            D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
    }
   
}