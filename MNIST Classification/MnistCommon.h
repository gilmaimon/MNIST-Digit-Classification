#pragma once
#include <cstdint>
#include <vector>

#define LITTLE_ENDIAN
#include "ByteOrder.h"
#include <tiny_dnn/io/cifar10_parser.h>

typedef tiny_dnn::vec_t PixelsVector;
typedef uint8_t Label;

struct MnistDataItem {
	PixelsVector imageData;
	Label label;
};

struct MnistDataSet {
	uint32_t numCols;
	uint32_t numRows;
	std::vector<MnistDataItem> trainDataItems;
};


const std::string g_trainingImagesFilename = "train-images.idx3-ubyte";
const std::string g_trainingLablesFilename = "train-labels.idx1-ubyte";

const std::string g_testgImagesFilename = "t10k-images.idx3-ubyte";
const std::string g_testgLabelsFilename = "t10k-labels.idx1-ubyte";

const std::string g_networkBackupFilename = "network_mode_weights.backup";
