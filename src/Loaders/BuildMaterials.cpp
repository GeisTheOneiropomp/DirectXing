#include "../DirectXing.h"
#include <DirectXColors.h>

void DirectXing::BuildMaterials()
{
    auto bricks0 = std::make_unique<Material>();
    bricks0->Name = "bricks0";
    bricks0->MatCBIndex = 0;
    bricks0->DiffuseSrvHeapIndex = 0;
    bricks0->NormalSrvHeapIndex = 1;
    bricks0->DiffuseAlbedo = DirectX::XMFLOAT4::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    bricks0->FresnelR0 = DirectX::XMFLOAT3::XMFLOAT3(0.1f, 0.1f, 0.1f);
    bricks0->Roughness = 0.3f;

    auto tile0 = std::make_unique<Material>();
    tile0->Name = "tile0";
    tile0->MatCBIndex = 5;
    tile0->DiffuseSrvHeapIndex = 2;
    tile0->NormalSrvHeapIndex = 3;
    tile0->DiffuseAlbedo = DirectX::XMFLOAT4::XMFLOAT4(DirectX::Colors::LightGray);
    tile0->FresnelR0 = DirectX::XMFLOAT3::XMFLOAT3(0.2f, 0.2f, 0.2f);
    tile0->Roughness = 0.2f;

    auto mirror0 = std::make_unique<Material>();
    mirror0->Name = "mirror0";
    mirror0->MatCBIndex = 2;
    mirror0->DiffuseSrvHeapIndex = 4;
    mirror0->NormalSrvHeapIndex = 5;
    mirror0->DiffuseAlbedo = DirectX::XMFLOAT4::XMFLOAT4(DirectX::Colors::LightSteelBlue);
    mirror0->FresnelR0 = DirectX::XMFLOAT3::XMFLOAT3(0.75f, 0.75f, 0.75f);
    mirror0->Roughness = 0.3f;

    auto sky = std::make_unique<Material>();
    sky->Name = "sky";
    sky->MatCBIndex = 3;
    sky->DiffuseSrvHeapIndex = 6;
    sky->NormalSrvHeapIndex = 7;
    sky->DiffuseAlbedo = DirectX::XMFLOAT4::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    sky->FresnelR0 = DirectX::XMFLOAT3::XMFLOAT3(0.1f, 0.1f, 0.1f);
    sky->Roughness = 1.0f;

    mMaterials[bricks0->Name] = std::move(bricks0);
    mMaterials[mirror0->Name] = std::move(mirror0);
    mMaterials[tile0->Name] = std::move(tile0);
    mMaterials[sky->Name] = std::move(sky);

}