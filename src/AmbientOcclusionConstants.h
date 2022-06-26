#pragma once
#include <DirectXCollision.h>

struct AmbientOcclusionConstants
{
    DirectX::XMFLOAT4X4 Proj;
    DirectX::XMFLOAT4X4 InvProj;
    DirectX::XMFLOAT4X4 ProjTex;
    DirectX::XMFLOAT4   OffsetVectors[14];

    DirectX::XMFLOAT4 BlurWeights[3];

    DirectX::XMFLOAT2 InvRenderTargetSize = { 0.0f, 0.0f };

    float OcclusionRadius = 0.5f;
    float OcclusionFadeStart = 0.2f;
    float OcclusionFadeEnd = 2.0f;
    float SurfaceEpsilon = 0.05f;
};