#include "Texture.h"

Texture::Texture(std::string Name, std::wstring Filename)
{
	this->Name = Name;
	this->Filename = Filename;
}

Microsoft::WRL::ComPtr<ID3D12Resource>& Texture::GetResource()
{
	return Resource;
}

Microsoft::WRL::ComPtr<ID3D12Resource>& Texture::GetUploadHeap()
{
	return UploadHeap;
}
