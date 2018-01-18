#include <iostream>
#include <cassert>
#include <memory>
#include "MnistCommon.h"
#include "MnistWindow.h"
#include "MnistDatasetReader.h"
#include "MnistNetwork.h"
#include "DrawableGreyscaleWindow.h"
#include "MnistDatasetReaderInterface.h"

#define LITTLE_ENDIAN
#include "ByteOrder.h"

std::shared_ptr<MnistWindow> CreateMnistTestWindow(const MnistDataItem dataItem = MnistDataItem{}) {
	std::shared_ptr<MnistWindow> result =
		std::make_shared<MnistWindow>(600, 600, "Mnist", dataItem);

	return result;
}

void DisplayMnistItem(const std::shared_ptr<IMnistWindow> window, const MnistDataItem& mnistDataItem) {
	window->SetDataItem(mnistDataItem);
	window->Draw();
	window->Display();
}

void LoadTrainingDataAndBackupNetwork(std::shared_ptr<IMnistDatasetReader> mnistDatasetReader, const size_t epochs) {
	//Load Training Dataset
	const MnistDataSet trainingDataSet = mnistDatasetReader->ReadTrainingDataset();
	std::cout << "Loaded Training Dataset" << std::endl;

	//Load Test Dataset
	const MnistDataSet testDataSet = mnistDatasetReader->ReadTestDataset();
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

void LoadNetworkAndPrintSucessRate(std::shared_ptr<IMnistDatasetReader> mnistDatasetReader) {
	MnistNetwork network;
	network.LoadFromFile(g_networkBackupFilename);

	const MnistDataSet testDataSet = mnistDatasetReader->ReadTestDataset();
	std::cout << "Loaded Test Dataset" << std::endl;
	std::cout << "Sucess Rate: " << network.SucessRate(testDataSet) * 100 << "%" << std::endl;

}

void ShowTestImagesAndPredictLables(const MnistDataSet& testDataset, const std::shared_ptr<IMnistAiModel> mnistNetwork) {
	
	auto mnistWindow = CreateMnistTestWindow();
	for (auto i = 0; i < 50; i++) {
		for (const auto& item : testDataset.trainDataItems) {
			DisplayMnistItem(mnistWindow, item);
			const char predicted = mnistNetwork->Predict(item);

			std::cout << "Predicted: " << predicted << std::endl;

			getchar();
		}
	}
}

void StartInteractiveDrawingPrediction(const std::shared_ptr<IMnistAiModel> mnistNetwork) {
	auto drawingWindow = std::make_unique<DrawableGreyscaleWindow>(450.0, 450.0, "Draw Here!", 28, 28);
	drawingWindow->SetBrushSize(2);

	char lastPrediction = '\0';
	while (drawingWindow->IsOpen()) {
		drawingWindow->HandleEvent();
		drawingWindow->Draw();
		drawingWindow->Display();

		const auto pixels = drawingWindow->FlatternToPixels();
		const char newPrediction = mnistNetwork->Predict(pixels);

		if (newPrediction != lastPrediction) {
			lastPrediction = newPrediction;
			std::cout << "Predicted: " << newPrediction << std::endl;
		}
	}
}

int main() {
	const byte_order::EndianessConverter currentConverter(byte_order::ByteOrder_BigEndian);
	std::shared_ptr<IMnistDatasetReader> mnistDatasetReader = std::make_shared<MnistDatasetReader>(
		g_trainingImagesFilename, g_trainingLablesFilename,
		g_testgImagesFilename, g_testgLabelsFilename,
		currentConverter
	);

	const std::shared_ptr<IMnistAiModel> mnistNetwork = std::make_shared<MnistNetwork>();
	mnistNetwork->LoadFromFile(g_networkBackupFilename);

	
	const auto testDataset = mnistDatasetReader->ReadTestDataset();	
	ShowTestImagesAndPredictLables(testDataset, mnistNetwork);
	

	StartInteractiveDrawingPrediction(mnistNetwork);

	getchar();
	return 0;
}
