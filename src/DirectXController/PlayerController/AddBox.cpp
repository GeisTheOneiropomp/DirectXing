#include "../../DirectXing.h"

void DirectXing::AddBox()
{
	if (mNumAddableBoxes == 5) {
		return;
	}
	else {
		std::vector<RenderItem*>& boxItems = mRitemLayer[(int)RenderLayer::Addable];
		RenderItem* box = boxItems[mNumAddableBoxes];
		auto drawDistance = mCamera.GetLook() * 3;
		auto positionVector = mCamera.GetPosition();
		auto x = XMVectorGetX(positionVector + drawDistance);
		auto y = XMVectorGetY(positionVector + drawDistance);
		auto z = XMVectorGetZ(positionVector + drawDistance);
		auto& secondItem = mAllRitems[box->ObjCBIndex];
		XMStoreFloat4x4(&box->World, XMMatrixTranslation(x, y, z));
		XMStoreFloat4x4(&secondItem->World, XMMatrixTranslation(x, y, z));
		mNumAddableBoxes++;
		box->NumFramesDirty = 3;
		secondItem->NumFramesDirty = 3;
	}
}