#include "MnistDatasetReader.h"

MnistDataSet MnistDatasetReader::ReadFromFiles(const std::string imagesFilename, const std::string labelsFilename,
                                               const int numToRead) const {
	//Read Images
	std::fstream imagesInputFile{imagesFilename, std::ios::binary | std::ios::in};
	std::vector<PixelsVector> images = ReadImagesFile(imagesInputFile, m_converter, numToRead);

	//Read Labels
	std::fstream labelsInputFile{labelsFilename, std::ios::binary | std::ios::in};
	std::vector<Label> labels = ReadLabelsFile(labelsInputFile, m_converter, numToRead);

	assert(images.size() == labels.size());

	//TODO i'm using 28 cause im lazy and mnist is kinda always 28x28 so its kinda legit..
	MnistDataSet resultDataSet;
	resultDataSet.numRows = resultDataSet.numCols = 28;

	for (size_t i = 0; i < images.size(); i++) {
		MnistDataItem item;
		item.imageData = std::move(images[i]);
		item.label = labels[i];
		resultDataSet.trainDataItems.push_back(std::move(item));
	}

	return resultDataSet;
}

MnistDatasetReader::MnistDatasetReader(const std::string trainingImagesFilename, const std::string trainingLabelsFilename,
	const std::string testImagesFilename, const std::string testLabelsFilename, const byte_order::EndianessConverter& converter) 
	: m_converter(converter), m_trainingImagesFilename(trainingImagesFilename),
	m_testImagesFilename(testImagesFilename), m_trainingLabelsFilename(g_trainingLablesFilename),
	m_testLabelsFilename(testLabelsFilename) {

}

std::vector<PixelsVector> MnistDatasetReader::ReadImagesFile(std::istream& imagesInputFile,
                                                             const byte_order::EndianessConverter& currentConverter,
                                                             const int numToRead) const {
	const auto magicNumber = ReadPrimitive<uint32_t>(imagesInputFile, currentConverter);
	const auto numImages = ReadPrimitive<uint32_t>(imagesInputFile, currentConverter);

	const auto numRows = ReadPrimitive<uint32_t>(imagesInputFile, currentConverter);
	const auto numCols = ReadPrimitive<uint32_t>(imagesInputFile, currentConverter);

	std::vector<PixelsVector> allImages;
	for (size_t iImage = 0; iImage < numImages; iImage++) {
		if (iImage == numToRead) break;

		PixelsVector image;
		for (size_t iPixel = 0; iPixel < numRows * numCols; iPixel++) {
			image.push_back(static_cast<float>(imagesInputFile.get()));
		}
		allImages.push_back(image);
	}


	return allImages;
}

std::vector<Label> MnistDatasetReader::ReadLabelsFile(std::istream& labelsInputFile,
                                                      const byte_order::EndianessConverter& currentConverter,
                                                      const int numToRead) const {
	const auto magicNumber = ReadPrimitive<uint32_t>(labelsInputFile, currentConverter);
	const auto numLabels = ReadPrimitive<uint32_t>(labelsInputFile, currentConverter);

	std::vector<Label> allLabels;
	for (size_t iLabel = 0; iLabel < numLabels; iLabel++) {
		if (iLabel == numToRead) break;

		Label label = labelsInputFile.get();
		allLabels.push_back(label);
	}

	return allLabels;
}

MnistDataSet MnistDatasetReader::ReadTrainingDataset() {
	return ReadFromFiles(m_trainingImagesFilename, m_trainingLabelsFilename, ReadAllFiles);
}

MnistDataSet MnistDatasetReader::ReadTestDataset() {
	return ReadFromFiles(m_testImagesFilename, m_testLabelsFilename, ReadAllFiles);
}