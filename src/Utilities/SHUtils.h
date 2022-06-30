#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class SHUtils
{
public:
	static double factorial(unsigned int y);
	static bool ParaboloidCoord(XMVECTOR* vec, int face, const XMVECTOR* uv);
	static void CubeCoord(XMVECTOR* vec, int face, const XMVECTOR* uv);
private:
	constexpr static double PI = 3.1415926535897932384626433;
};

