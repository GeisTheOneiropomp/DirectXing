#pragma once
#include "../Utilities/Texture.h"
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <memory>

class TextureLoader
{
public:
	 void Load(
		 Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
		 Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		 std::unordered_map<std::string, std::unique_ptr<Texture>>* textures);
private:
	  std::vector<std::tuple<std::string, std::wstring>> texStrings = { 
		std::make_tuple("bricksDiffuseMap",L"../Assets/bricks3.dds"),
		std::make_tuple("bricksNormalMap",L"../Assets/bricks2_nmap.dds"),
		std::make_tuple("tileDiffuseMap",L"../Assets/tile.dds"),
		std::make_tuple("tileNormalMap",L"../Assets/tile_nmap.dds"),
		std::make_tuple("defaultDiffuseMap",L"../Assets/white1x1.dds"),
		std::make_tuple("defaultNormalMap",L"../Assets/default_nmap.dds"),
		std::make_tuple("skyCubeMap", L"../Assets/grasscube1024.dds"),
	};

};