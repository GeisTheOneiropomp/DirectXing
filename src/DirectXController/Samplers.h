#pragma once
#include "../ext/d3dx12.h"
#include <array>
 
class Samplers {
public:
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> GetStaticSamplers();
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 4> GetSSAOSamplers();
private:
	static CD3DX12_STATIC_SAMPLER_DESC GetPointWrapSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetPointClampSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearWrapSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearClampSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicWrapSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicClampSampler(int position);
	static CD3DX12_STATIC_SAMPLER_DESC GetShadowSampler(int position, int maxAnisotropy);
};