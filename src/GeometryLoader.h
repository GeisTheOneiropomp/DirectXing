#pragma once
#include <unordered_map>
#include <memory>
#include "../Utilities/MeshGeometry.h"

class GeometryLoader
{
public:
	void Load(
		Microsoft::WRL::ComPtr<ID3D12Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList,
		std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>* geometries);
private:
};

