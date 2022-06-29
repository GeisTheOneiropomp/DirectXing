#pragma once
#include <string>
#include <DirectXMath.h>
#include "../Utilities/MathHelper.h"
#include "Constants/ConfigConstants.h"
class Material
{
public:
    std::string Name;

    int MatCBIndex = -1;

    int DiffuseSrvHeapIndex = -1;

    int NormalSrvHeapIndex = -1;

    int NumFramesDirty = CONFIG_CONST_NUM_FRAMES;

    DirectX::XMFLOAT4 DiffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
    DirectX::XMFLOAT3 FresnelR0 = { 0.01f, 0.01f, 0.01f };
    float Roughness = .25f;
    DirectX::XMFLOAT4X4 MatTransform = MathHelper::Identity4x4();
};


