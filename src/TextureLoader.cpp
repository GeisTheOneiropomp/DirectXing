#include "TextureLoader.h"
#include "../Utilities/DirectXUtilities.h"

void TextureLoader::Load(
    Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
    std::unordered_map<std::string, std::unique_ptr<Texture>>* textures)
{
    for (auto texString : texStrings) {
        auto texMap = std::make_unique<Texture>(std::get<0>(texString), std::get<1>(texString));
        ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(d3dDevice.Get(),
            commandList.Get(), texMap->Filename.c_str(),
            texMap->GetResource(), texMap->GetUploadHeap()));
        (*textures)[texMap->Name] = std::move(texMap);
    }
}
