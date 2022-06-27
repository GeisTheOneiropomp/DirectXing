#include "SHUtils.h"

double SHUtils::factorial(unsigned int y)
{
	assert(y < 16);
	const double table[16] = { 1., 1., 2., 6., 24., 120., 720., 5040., 40320., 362880.,
		3628800., 39916800., 479001600., 6227020800., 87178291200., 1307674368000. };
	return table[y];
}

void SHUtils::CubeCoord(XMVECTOR* vec, int face, const XMVECTOR* uv)
{
    XMVECTOR tmp;
    switch (face)
    {
    case 0: tmp = _mm_set_ps(1.f, -XMVectorGetY(*uv), -XMVectorGetX(*uv), 0.0f); break;
    case 1: tmp = _mm_set_ps(-1.f, -XMVectorGetY(*uv), XMVectorGetX(*uv), 0.0f); break;
    case 2: tmp = _mm_set_ps(XMVectorGetX(*uv), 1.f, XMVectorGetY(*uv), 0.0f); break;
    case 3: tmp = _mm_set_ps(XMVectorGetX(*uv), -1.f, -XMVectorGetY(*uv), 0.0f); break;
    case 4: tmp = _mm_set_ps(XMVectorGetX(*uv), -XMVectorGetY(*uv), 1.f, 0.0f); break;
    case 5: tmp = _mm_set_ps(-XMVectorGetX(*uv), -XMVectorGetY(*uv), -1.f, 0.0f); break;
    }
    auto normalized = XMVector3Normalize(tmp) ;
    *vec = _mm_set_ps(XMVectorGetZ(normalized), -XMVectorGetX(normalized), XMVectorGetY(normalized), 1.f) ;
    //*vec = tmp;
}

bool SHUtils::ParaboloidCoord(XMVECTOR* vec, int face, const XMVECTOR* uv)
{
    //  sphere direction is the reflection of the orthographic view direction (determined by
    //  face), reflected about the normal to the paraboloid at uv
    long squaredRadius = XMVectorGetX(*uv) * XMVectorGetX(*uv) + XMVectorGetY(*uv) * XMVectorGetY(*uv);

    if (squaredRadius > 1.)
        return false;

    XMVECTOR axis;
    if (face == 0)
        axis =  _mm_set_ps(0.0f, 0.0f, -1.f, 0.0f);
    else
        axis = _mm_set_ps(0.0f, 0.0f, 1.f, 0.0f);

    // compute normal on the parabaloid at uv
    XMVECTOR N = _mm_set_ps(XMVectorGetX(*uv), XMVectorGetY(*uv), 1.f, 0.0f);
    auto normalizedN = XMVector3Normalize(N);

    // reflect axis around N, to compute sphere direction
    float vDotN = XMVectorGetX(XMVector3Dot(axis, N));
    *vec = axis - 2 * vDotN * N;

    return true;
}


