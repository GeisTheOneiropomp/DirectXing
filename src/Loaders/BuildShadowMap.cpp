#include "../DirectXing.h"

void DirectXing::MakeShadowMap() {
    mShadowMap = std::make_unique<ShadowMap>(md3dDevice.Get(), 2048, 2048);
}