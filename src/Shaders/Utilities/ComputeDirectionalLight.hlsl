#include "Utilities/BlinnPhong.hlsl"
#include "Utilities/Light.hlsl"
#include "Utilities/Material.hlsl"

#ifndef __COMPUTEDIRECTIONALLIGHT_HLSL__
#define __COMPUTEDIRECTIONALLIGHT_HLSL__

float3 ComputeDirectionalLight(Light L, Material mat, float3 normal, float3 toEye)
{
    // The light vector aims opposite the direction the light rays travel.
    float3 lightVec = -L.Direction;

    // Scale light down by Lambert's cosine law.
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightStrength = L.Strength * ndotl;

    return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

#endif