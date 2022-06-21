#include "../Utilities/d3dApp.h"
#include "../Utilities/MathHelper.h"
#include "../Utilities/UploadBuffer.h"
#include "FrameResource.h"
#include "RenderItem.h"
#include "../Utilities/Camera.h"
#include "../Utilities/Samplers.h"
#include "../Utilities/RenderLayer.h"
#include "TextureLoader.h"
#include "MaterialLoader.h"
#include "GeometryLoader.h"
#include "PSOBuilder.h"
#include "RenderItemBuilder.h"
#include "ConfigConstants.h"
#include "DescriptorHeapBuilder.h"
#include "ShadowMap.h"
#include "ShadersLoader.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

struct VertexPosition
{
    XMFLOAT3 Pos;
};

struct VertexColor
{
    XMFLOAT4 Color;
};

class BoxApp : public D3DApp
{
public:
    BoxApp(HINSTANCE hInstance);
    BoxApp(const BoxApp& rhs) = delete;
    BoxApp& operator=(const BoxApp& rhs) = delete;
    ~BoxApp();

    virtual bool Initialize()override;

private:
    virtual void OnResize()override;
    virtual void Update(const GameTimer& gt)override;
    virtual void Draw(const GameTimer& gt)override;

    virtual void OnMouseDown(WPARAM btnState, int x, int y)override;
    virtual void OnMouseUp(WPARAM btnState, int x, int y)override;
    virtual void OnMouseMove(WPARAM btnState, int x, int y)override;
    virtual void CreateRtvAndDsvDescriptorHeaps()override;

    void OnKeyboardInput(const GameTimer& gt);

    void BuildRootSignature();
    void BuildShadersAndInputLayout();
    void BuildShapeGeometry();
    void BuildPSO();
    void AnimateMaterials(const GameTimer& gt);
    void BuildMaterials();
    void LoadTextures();
    void UpdateObjectCBs(const GameTimer& gt);
    void UpdateMainPassCB(const GameTimer& gt);
    void UpdateMaterialCBs(const GameTimer& gt);

    void BuildRenderItems();

    void BuildFrameResources();

    void BuildDescriptorHeaps();

    void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

    void MakeShadowMap();
    void UpdateShadowPassCB(const GameTimer& gt);
    void UpdateShadowTransform(const GameTimer& gt);
    void DrawSceneToShadowMap();

private:

    ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
    ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;
    Samplers mSamplers;

    std::vector<std::unique_ptr<FrameResource>> mFrameResources;
    FrameResource* mCurrFrameResource = nullptr;
    int mCurrFrameResourceIndex = 0;

    UINT mCbvSrvDescriptorSize = 0;


    std::vector<std::unique_ptr<RenderItem>> mAllRitems;
    std::vector<RenderItem*> mRitemLayer[(int)RenderLayer::Count];

    PassConstants mMainPassCB;

    std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
    std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;
    std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;
    std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

    std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

    std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

    UINT mPassCbvOffset = 0;

    float mTheta = 1.5f * XM_PI;
    float mPhi = 0.2f * XM_PI;
    float mRadius = 15.0f;

    POINT mLastMousePos;
    bool mIsWireframe = false;

    Camera mCamera;
    
    UINT mSkyTexHeapIndex = 0;
    UINT mShadowMapHeapIndex = 0;
    UINT mNullCubeSrvIndex = 0;
    UINT mNullTexSrvIndex = 0;

    // shadow map variables
    float mLightNearZ = 0.0f;
    float mLightFarZ = 0.0f;
    XMFLOAT3 mLightPosW;
    XMFLOAT4X4 mLightView = MathHelper::Identity4x4();
    XMFLOAT4X4 mLightProj = MathHelper::Identity4x4();
    XMFLOAT4X4 mShadowTransform = MathHelper::Identity4x4();
    PassConstants mShadowPassCB;// index 1 of pass cbuffer.
    std::unique_ptr<ShadowMap> mShadowMap;
    CD3DX12_GPU_DESCRIPTOR_HANDLE mNullSrv;

    float mLightRotationAngle = 0.0f;
    XMFLOAT3 mBaseLightDirections[3] = {
        XMFLOAT3(0.57735f, -0.57735f, 0.57735f),
        XMFLOAT3(-0.57735f, -0.57735f, 0.57735f),
        XMFLOAT3(0.0f, -0.707f, -0.707f)
    };
    XMFLOAT3 mRotatedLightDirections[3];
    DirectX::BoundingSphere mBounds;
}; 
