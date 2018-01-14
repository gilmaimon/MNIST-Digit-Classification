#pragma once
#include "MnistCommon.h"
#include <fstream>
#include <cassert>

class MnistDatasetReader {
public:
	explicit MnistDatasetReader(const byte_order::EndianessConverter& converter);

	MnistDataSet ReadFromFiles(const std::string imagesFilename, const std::string labelsFilename, const int numToRead) const;
private:
	byte_order::EndianessConverter m_converter;

	template <typename PrimitiveType> PrimitiveType ReadPrimitive(std::istream& is,
		const byte_order::EndianessConverter& converter) const {
		static_assert(std::is_fundamental<PrimitiveType>::value, "Type sent to ReadPrimitive must be primitive");

		PrimitiveType value;
		is.read(reinterpret_cast<char *>(&value), sizeof(value));
		return converter.ResolveEndianess(value);
	}

	std::vector<PixelsVector> ReadImagesFile(std::istream& imagesInputFile,
	                                         const byte_order::EndianessConverter& currentConverter, const int numToRead) const;

	std::vector<Label> ReadLabelsFile(std::istream& labelsInputFile,
	                                  const byte_order::EndianessConverter& currentConverter, const int numToRead) const;
};
