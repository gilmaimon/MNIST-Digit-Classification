#include <iostream>
#include <vector>
#include <cassert>
#include <memory>
#include "MnistCommon.h"
#include "MnistWindow.h"
#include "MnistDatasetReader.h"
#include "MnistNetwork.h"
#include "DrawableGreyscaleWindow.h"

#define LITTLE_ENDIAN
#include "ByteOrder.h"

std::unique_ptr<MnistWindow> CreateMnistTestWindow(const MnistDataItem dataItem = MnistDataItem{}) {
	std::unique_ptr<MnistWindow> result =
		std::make_unique<MnistWindow>(600, 600, "Mnist", dataItem);

	return result;
}

void DisplayMnistItem(const std::unique_ptr<MnistWindow>& window, const MnistDataItem& mnistDataItem) {
	window->SetDataItem(mnistDataItem);
	window->Draw();
	window->Display();
}

void LoadTrainingDataAndBackupNetwork(const size_t trainingSamples, const size_t testSamples, const size_t epochs) {
	const byte_order::EndianessConverter currentConverter(byte_order::ByteOrder_BigEndian);
	const MnistDatasetReader mnistDatasetReader{ currentConverter };

	//Load Training Dataset
	const MnistDataSet trainingDataSet = mnistDatasetReader.ReadFromFiles(
		g_trainingImagesFilename,
		g_trainingLablesFilename,
		trainingSamples
	);
	std::cout << "Loaded Training Dataset" << std::endl;

	//Load Test Dataset
	const MnistDataSet testDataSet = mnistDatasetReader.ReadFromFiles(
		g_testgImagesFilename,
		g_testgLabelsFilename,
		testSamples
	);
	std::cout << "Loaded Test Dataset" << std::endl;

	//Construct Network
	MnistNetwork network{ trainingDataSet.numRows, trainingDataSet.numCols };
	std::cout << "Constructed Network" << std::endl;
	
	network.LoadFromFile(g_networkBackupFilename);
	std::cout << "Loaded Network" << std::endl;

	//Train Wanted Number of Epochs
	std::cout << "Sucess Rate: " << network.SucessRate(testDataSet) * 100 << "%" << std::endl;
	for(size_t epoch = 0; epoch < epochs; epoch++) {
		network.Train(trainingDataSet);
		std::cout << "Trained Network" << std::endl;
		std::cout << "Sucess Rate: " << network.SucessRate(testDataSet) * 100 << "%" << std::endl;

		network.SaveToFile(g_networkBackupFilename);
		std::cout << "Saved Network" << std::endl;
	}
}

void LoadNetworkAndPrintSucessRate() {
	MnistNetwork network;
	network.LoadFromFile(g_networkBackupFilename);

	const byte_order::EndianessConverter currentConverter(byte_order::ByteOrder_BigEndian);
	const MnistDatasetReader mnistDatasetReader{ currentConverter };

	const MnistDataSet testDataSet = mnistDatasetReader.ReadFromFiles(
		g_testgImagesFilename,
		g_testgLabelsFilename,
		-1
	);
	std::cout << "Loaded Test Dataset" << std::endl;
	std::cout << "Sucess Rate: " << network.SucessRate(testDataSet) * 100 << "%" << std::endl;

}

int main() {
	//LoadTrainingDataAndBackupNetwork(-1, -1, 5);
	//LoadNetworkAndPrintSucessRate();

	DrawableGreyscaleWindow window;

	MnistNetwork network;
	network.LoadFromFile(g_networkBackupFilename);

	char lastPrediction = '\0';
	while(window.IsOpen()) {
		window.HandleEvent();
		window.Draw();
		window.Display();

		const auto pixels = window.FlatternImage();
		const char newPrediction = network.Predict(pixels);

		if(newPrediction != lastPrediction) {
			lastPrediction = newPrediction;
			std::cout << "Predicted: " << newPrediction << std::endl;
		}
	}

	/*
	for (auto i = 0; i < 50; i++) {
		for (const auto& item : testDataSet.trainDataItems) {
			DisplayMnistItem(window, item);
			const char predicted = network.Predict(item);

			std::cout << "Predicted: " << predicted << std::endl;
			getchar();
		}
	}
	*/

	getchar();
	return 0;
}
