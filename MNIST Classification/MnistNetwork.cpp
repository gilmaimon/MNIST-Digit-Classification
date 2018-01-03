#include "MnistNetwork.h"
#include <tiny_dnn\tiny_dnn.h>

MnistNetwork::MnistNetwork(const size_t numRows, const size_t numCols) {
	InitMnistNetwork(numRows, numCols);
	m_optimizer.alpha = 0.1f;
}

MnistNetwork::MnistNetwork() { }

void MnistNetwork::Train(const MnistDataItem& item) {
	tiny_dnn::vec_t outputLabel(10, 0);
	outputLabel[item.label] = 1;

	m_network.train<tiny_dnn::mse>(m_optimizer, {item.imageData}, {outputLabel});
}

void MnistNetwork::Train(const MnistDataSet& items) {
	for (auto& item : items.trainDataItems) {
		Train(item);
	}
}

float MnistNetwork::SucessRate(const MnistDataSet& items) {
	size_t successfulPredictions = 0;

	for (auto& item : items.trainDataItems) {
		if (Predict(item) == static_cast<char>('0' + item.label)) {
			++successfulPredictions;
		}
	}

	return static_cast<float>(successfulPredictions) / items.trainDataItems.size();
}

char MnistNetwork::Predict(const MnistDataItem& item) {
	return Predict(item.imageData);
}

char MnistNetwork::Predict(const PixelsVector& piexelsVector) {
	auto result = m_network.predict(piexelsVector);

	const auto maximumIdx = std::distance(result.begin(), std::max_element(result.begin(), result.end()));
	return '0' + maximumIdx;
}

void MnistNetwork::SaveToFile(const std::string filename) {
	m_network.save(filename);
}

void MnistNetwork::LoadFromFile(const std::string filename) {
	m_network.load(filename);
}

#include <tiny_dnn\layers\convolutional_layer.h>
#include <tiny_dnn\layers\average_pooling_layer.h>
#include <tiny_dnn\layers\fully_connected_layer.h>
#include <tiny_dnn\activations\tanh_layer.h>

void MnistNetwork::InitMnistNetwork(const size_t numRows, const size_t numCols) {
	using namespace tiny_dnn;

	m_network << convolutional_layer(numCols, numRows, 5, 1, 6) << tanh_layer();
	m_network << average_pooling_layer(numCols - 4, numRows - 4, 6, 2) << tanh_layer();
	m_network << fully_connected_layer(((numCols - 4) / 2) * ((numCols - 4) / 2) * 6, 100) << tanh_layer();
	m_network << fully_connected_layer(100, 10);
	m_network.init_weight();
}
