#include "../DirectXing.h"

void DirectXing::SetBounds() {
	mBounds.Center = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mBounds.Radius = sqrtf(10.0f * 10.0f + 15.0f * 15.0f);
}
