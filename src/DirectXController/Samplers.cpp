#include "Samplers.h"

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> Samplers::GetStaticSamplers() {
	return { GetPointWrapSampler(0),
			 GetPointClampSampler(1),
			 GetLinearWrapSampler(2),
			 GetLinearClampSampler(3),
			 GetAnisotropicWrapSampler(4),
			 GetAnisotropicClampSampler(5),
			 GetShadowSampler(6, 16) };
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 4> Samplers::GetSSAOSamplers() {
	return { GetPointClampSampler(0),
			 GetLinearClampSampler(1),
			 GetShadowSampler(2, 0),
			 GetLinearWrapSampler(3) };
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetPointWrapSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetPointClampSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetLinearWrapSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetLinearClampSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetAnisotropicWrapSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetAnisotropicClampSampler(int position) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy
}

CD3DX12_STATIC_SAMPLER_DESC Samplers::GetShadowSampler(int position, int maxAnisotropy) {
	return CD3DX12_STATIC_SAMPLER_DESC(
		position, // shaderRegister
		D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,  // addressW
		0.0f,                              // mipLODBias
		maxAnisotropy,
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK);
}