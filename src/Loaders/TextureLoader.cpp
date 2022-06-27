#include "../DirectXing.h"
#include "../Utilities/DirectXUtilities.h"

void DirectXing::LoadTextures()
{
	std::vector<std::tuple<std::string, std::wstring>> texStrings = {
        std::make_tuple("bricksDiffuseMap",L"../Assets/bricks3.dds"),
        std::make_tuple("bricksNormalMap",L"../Assets/bricks2_nmap.dds"),
        std::make_tuple("tileDiffuseMap",L"../Assets/tile.dds"),
        std::make_tuple("tileNormalMap",L"../Assets/tile_nmap.dds"),
        std::make_tuple("defaultDiffuseMap",L"../Assets/white1x1.dds"),
        std::make_tuple("defaultNormalMap",L"../Assets/default_nmap.dds"),
        std::make_tuple("skyCubeMap", L"../Assets/grasscube1024.dds"),
	};

    for (auto texString : texStrings) {
        auto texMap = std::make_unique<Texture>(std::get<0>(texString), std::get<1>(texString));
        ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
            mCommandList.Get(), texMap->Filename.c_str(),
            texMap->GetResource(), texMap->GetUploadHeap()));
        mTextures[texMap->Name] = std::move(texMap);
    }
}
