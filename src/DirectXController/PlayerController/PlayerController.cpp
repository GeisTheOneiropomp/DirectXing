#include "../../DirectXing.h"

void DirectXing::OnMouseDown(WPARAM btnState, int x, int y)
{
    mLastMousePos.x = x;
    mLastMousePos.y = y;

    SetCapture(mhMainWnd);
}

void DirectXing::OnMouseUp(WPARAM btnState, int x, int y)
{
    ReleaseCapture();
}

void DirectXing::OnMouseMove(WPARAM btnState, int x, int y)
{
    if ((btnState & MK_LBUTTON) != 0)
    {
        // Make each pixel correspond to a quarter of a degree.
        float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
        float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

        mCamera.Pitch(dy);
        mCamera.RotateY(dx);
    }

    mLastMousePos.x = x;
    mLastMousePos.y = y;
}

void DirectXing::OnKeyboardInput(const GameTimer& gt)
{
    const float dt = gt.DeltaTime();
    if (gt.TotalTime() - mLastToggleTime > .2) {
        if (GetAsyncKeyState('1') & 0x8000) {
            mUseShadowMap = !mUseShadowMap;
            mLastToggleTime = gt.TotalTime();
        }
        if (GetAsyncKeyState('2') & 0x8000) {
            mUseSSAO = !mUseSSAO;
            mLastToggleTime = gt.TotalTime();
        }
    }
    if (GetAsyncKeyState('W') & 0x8000)
        mCamera.Walk(10.0f * dt);
    if (GetAsyncKeyState('S') & 0x8000)
        mCamera.Walk(-10.0f * dt);
    if (GetAsyncKeyState('A') & 0x8000)
        mCamera.Strafe(-10.0f * dt);
    if (GetAsyncKeyState('D') & 0x8000)
        mCamera.Strafe(10.0f * dt);
    mCamera.UpdateViewMatrix();
}