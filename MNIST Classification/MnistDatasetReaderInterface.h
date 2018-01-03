#pragma once
#include "MnistCommon.h"

struct IMnistDatasetReader {
	virtual ~IMnistDatasetReader() = default;
	virtual MnistDataSet ReadTrainingDataset() = 0;
	virtual MnistDataSet ReadTestDataset() = 0;
};