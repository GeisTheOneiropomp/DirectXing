#include "../../DirectXing.h"

void DirectXing::DrawSSAOInstructions()
{
    if (mUseSSAO) {
        mCommandList->SetGraphicsRootSignature(mSsaoRootSignature.Get());
        mSSAmbientOcclusion->ComputeSsao(mCommandList.Get(), mCurrFrameResource, 3);
    }
    else {
        mCommandList->SetGraphicsRootSignature(mSsaoRootSignature.Get());
        mSSAmbientOcclusion->WashSSAO(mCommandList.Get(), mCurrFrameResource);
    }
}