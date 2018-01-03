#pragma once
#include "MnistCommon.h"

struct IFlatternToPixels {
	virtual PixelsVector FlatternToPixels() const = 0;
	virtual ~IFlatternToPixels() = default;
};