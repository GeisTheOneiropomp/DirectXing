#include "../DirectXing.h"

void DirectXing::LoadSSAmbientOcclusion() {
	mSSAmbientOcclusion = std::make_unique<SSAmbientOcclusion>(md3dDevice.Get(),
		mCommandList.Get(), mClientWidth, mClientHeight);
}