#pragma once
#include "MnistCommon.h"

struct MnistNetworkInterface {
	virtual void Train(const MnistDataItem& item) = 0;
	virtual void Train(const MnistDataSet& item) = 0;
	virtual char Predict(const MnistDataItem& item) = 0;
	virtual char Predict(const PixelsVector& piexelsVector) = 0;
	virtual float SucessRate(const MnistDataSet& item) = 0;
	virtual ~MnistNetworkInterface() = default;
};
