#ifndef __MATERIAL_HLSL__
#define __MATERIAL_HLSL__

struct Material
{
    float4 DiffuseAlbedo;
    float3 FresnelR0;
    float Shininess;
};

#endif