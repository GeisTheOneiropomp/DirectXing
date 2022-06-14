#ifndef __LIGHTATTENUATION_HLSL__
#define __LIGHTATTENUATION_HLSL__


float LightAttenuation(float d, float falloffStart, float falloffEnd)
{
    // Linear falloff.
    return saturate((falloffEnd-d) / (falloffEnd - falloffStart));
}

#endif