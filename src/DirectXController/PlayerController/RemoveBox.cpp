#include "../../DirectXing.h"

void DirectXing::RemoveBox()
{
	if (mNumAddableBoxes == 0) {
		return;
	}
	else {
		mNumAddableBoxes--;
	}
}