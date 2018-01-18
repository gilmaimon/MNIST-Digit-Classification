#pragma once
#include "MnistCommon.h"
#include "BackupInterface.h"

struct IMnistAiModel : public virtual IBackup {
	virtual void Train(const MnistDataItem& item) = 0;
	virtual void Train(const MnistDataSet& item) = 0;
	virtual char Predict(const MnistDataItem& item) = 0;
	virtual char Predict(const PixelsVector& piexelsVector) = 0;
	virtual float SucessRate(const MnistDataSet& item) = 0;
	virtual ~IMnistAiModel() = default;
};
