#include "../DirectXing.h"

void DirectXing::BuildFrameResources()
{
    for (int i = 0; i < CONFIG_CONST_NUM_FRAMES; ++i)
    {
        mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
            2, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
    }
}