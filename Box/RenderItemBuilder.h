#pragma once
#include <vector>
#include <unordered_map>
#include <d3d12.h>
#include <memory>
#include "../Utilities/Material.h"
#include "../Utilities/MeshGeometry.h"
#include "RenderItem.h"
#include "../Utilities/RenderLayer.h"

class RenderItemBuilder
{
public:
	void Load(
        std::unordered_map<std::string, std::unique_ptr<Material>> * materials,
        std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> * geometries,
        std::vector<RenderItem*> * rItemLayer,
        std::vector<std::unique_ptr<RenderItem>> * allRitems
    );

private:
};