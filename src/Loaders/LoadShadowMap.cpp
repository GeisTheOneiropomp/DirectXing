#include "../DirectXing.h"

void DirectXing::LoadShadowMap() {
	mShadowMap = std::make_unique<ShadowMap>(md3dDevice.Get(), 2048, 2048);
}