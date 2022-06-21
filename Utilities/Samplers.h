#pragma once
#include "d3dx12.h"
#include <array>
 
class Samplers {
public:
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();
private:
	static CD3DX12_STATIC_SAMPLER_DESC GetPointWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetPointClampSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearClampSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicClampSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetShadowSampler();
};