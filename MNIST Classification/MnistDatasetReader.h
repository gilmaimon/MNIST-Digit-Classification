#pragma once
#include "MnistCommon.h"
#include <fstream>
#include <cassert>
#include "MnistDatasetReaderInterface.h"

class MnistDatasetReader : public IMnistDatasetReader {
public:
	explicit MnistDatasetReader(const std::string trainingImagesFilename, const std::string trainingLabelsFilename,
		const std::string testImagesFilename, const std::string testLabelsFilename, const byte_order::EndianessConverter& converter);
	
	virtual MnistDataSet ReadTrainingDataset() final override;
	virtual MnistDataSet ReadTestDataset() final override;

private:	
	static const int ReadAllFiles = -1;

	byte_order::EndianessConverter m_endianessconverter;
	const std::string m_trainingImagesFilename, m_trainingLabelsFilename;
	const std::string m_testImagesFilename, m_testLabelsFilename;

	MnistDataSet ReadFromFiles(const std::string imagesFilename, const std::string labelsFilename, const int numToRead) const;


	template <typename PrimitiveType> PrimitiveType ReadPrimitive(std::istream& is,
		const byte_order::EndianessConverter& converter) const {
		static_assert(std::is_fundamental<PrimitiveType>::value, "Type sent to ReadPrimitive must be fundamental");

		PrimitiveType value;
		is.read(reinterpret_cast<char *>(&value), sizeof(value));
		return converter.ResolveEndianess(value);
	}

	std::vector<PixelsVector> ReadImagesFile(std::istream& imagesInputFile,
	                                         const byte_order::EndianessConverter& currentConverter, const int numToRead) const;
	
	std::vector<Label> ReadLabelsFile(std::istream& labelsInputFile,
	                                  const byte_order::EndianessConverter& currentConverter, const int numToRead) const;
};
