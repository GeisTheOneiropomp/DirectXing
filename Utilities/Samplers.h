#pragma once
#include "d3dx12.h"
#include <array>
 
class Samplers {
public:
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();
private:
	static CD3DX12_STATIC_SAMPLER_DESC GetPointWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetPointClampSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetLinearClampSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicWrapSampler();
	static CD3DX12_STATIC_SAMPLER_DESC GetAnisotropicClampSampler();
};

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> Samplers::GetStaticSamplers() {
	return { GetPointWrapSampler(), 
			 GetPointClampSampler(), 
			 GetLinearWrapSampler(), 
			 GetLinearClampSampler(),
			 GetAnisotropicWrapSampler(),
			 GetAnisotropicClampSampler() };
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetPointWrapSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC (
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetPointClampSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC (
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetLinearWrapSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetLinearClampSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetAnisotropicWrapSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetAnisotropicClampSampler() {
	return CD3DX12_STATIC_SAMPLER_DESC(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy
}