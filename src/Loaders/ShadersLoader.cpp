#include "ShadersLoader.h"
#include "../Utilities/DirectXUtilities.h"

void ShadersLoader::Load(std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3DBlob>> * shaders, 
	std::vector<D3D12_INPUT_ELEMENT_DESC> * layout)
{
    const D3D_SHADER_MACRO alphaTestDefines[] =
    {
        "ALPHA_TEST", "1",
        NULL, NULL
    };

    (*shaders)["standardVS"] = DirectXUtilities::CompileShader(L"Shaders\\Default.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["opaquePS"] = DirectXUtilities::CompileShader(L"Shaders\\Default.hlsl", nullptr, "PS", "ps_5_1");

    (*shaders)["shadowVS"] = DirectXUtilities::CompileShader(L"Shaders\\Shadows.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["shadowOpaquePS"] = DirectXUtilities::CompileShader(L"Shaders\\Shadows.hlsl", nullptr, "PS", "ps_5_1");
    (*shaders)["shadowAlphaTestedPS"] = DirectXUtilities::CompileShader(L"Shaders\\Shadows.hlsl", alphaTestDefines, "PS", "ps_5_1");

    (*shaders)["debugVS"] = DirectXUtilities::CompileShader(L"Shaders\\ShadowDebug.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["debugPS"] = DirectXUtilities::CompileShader(L"Shaders\\ShadowDebug.hlsl", nullptr, "PS", "ps_5_1");

    (*shaders)["drawNormalsVS"] = DirectXUtilities::CompileShader(L"Shaders\\DrawNormals.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["drawNormalsPS"] = DirectXUtilities::CompileShader(L"Shaders\\DrawNormals.hlsl", nullptr, "PS", "ps_5_1");

    (*shaders)["skyVS"] = DirectXUtilities::CompileShader(L"Shaders\\Skybox.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["skyPS"] = DirectXUtilities::CompileShader(L"Shaders\\Skybox.hlsl", nullptr, "PS", "ps_5_1");

    (*shaders)["ssaoVS"] = DirectXUtilities::CompileShader(L"Shaders\\Ssao.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["ssaoPS"] = DirectXUtilities::CompileShader(L"Shaders\\Ssao.hlsl", nullptr, "PS", "ps_5_1");

    (*shaders)["ssaoBlurVS"] = DirectXUtilities::CompileShader(L"Shaders\\SsaoBlur.hlsl", nullptr, "VS", "vs_5_1");
    (*shaders)["ssaoBlurPS"] = DirectXUtilities::CompileShader(L"Shaders\\SsaoBlur.hlsl", nullptr, "PS", "ps_5_1");

    //TODO: automate this
    *layout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
}
