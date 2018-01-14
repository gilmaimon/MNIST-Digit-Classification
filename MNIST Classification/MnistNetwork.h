#pragma once
#include <tiny_dnn/tiny_dnn.h>
#include "MnistNetworkInterface.h"
#include "BackupAble.h"

class MnistNetwork : public MnistNetworkInterface, public BackupAble {
public:
	explicit MnistNetwork(const size_t numRows, const size_t numCols);
	explicit MnistNetwork();

	virtual void Train(const MnistDataItem& item) override;
	virtual void Train(const MnistDataSet& items) override;

	virtual float SucessRate(const MnistDataSet& items) override;
	virtual char Predict(const MnistDataItem& item) override;
	virtual char Predict(const PixelsVector& piexelsVector) override;

	virtual void SaveToFile(const std::string filename) override;
	virtual void LoadFromFile(const std::string filename) override;

	virtual ~MnistNetwork() override = default;
private:
	tiny_dnn::gradient_descent m_optimizer;
	tiny_dnn::network<tiny_dnn::sequential> m_network;
	void InitMnistNetwork(const size_t numRows, const size_t numCols);
};