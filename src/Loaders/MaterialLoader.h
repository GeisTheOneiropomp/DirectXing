#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include "../DirectXController/Material.h"

class MaterialLoader
{
public:
	void Load(std::unordered_map<std::string, std::unique_ptr<Material>>* materials);
private:

};