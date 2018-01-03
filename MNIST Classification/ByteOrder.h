#pragma once
#include <stdlib.h>
#include <type_traits>
#include <cstdint>

namespace byte_order {
	enum ByteOrder {
		ByteOrder_LittleEndian,
		ByteOrder_BigEndian
	};

	inline uint64_t FlipEndianess(const uint64_t value) {
		return _byteswap_uint64(value);
	}

	inline uint32_t FlipEndianess(const uint32_t value) {
		return _byteswap_ulong(value);
	}

	inline uint16_t FlipEndianess(const uint16_t value) {
		return _byteswap_ushort(value);
	}

	inline uint8_t FlipEndianess(const uint8_t value) {
		return value;
	}

	template <typename PrimitiveType>
	PrimitiveType ConvertEndianess(const PrimitiveType value,
							  const ByteOrder sourceEndian,
							  const ByteOrder targetEndian) {
		static_assert(std::is_fundamental<PrimitiveType>::value, "Type sent to ConvertEndianess must be primitive");		
		if (sourceEndian == targetEndian) return value;
		return FlipEndianess(value);
	}

	class EndianessConverter {
	public:
		explicit EndianessConverter(const ByteOrder sourceByteOrder): m_sourceByteOrder(sourceByteOrder) { }

		template <class PrimitiveType> PrimitiveType ResolveEndianess(const PrimitiveType value) const {
			return ConvertEndianess(value, m_sourceByteOrder, m_destinationByteOrder);
		}

	private:
		ByteOrder m_sourceByteOrder;
#ifdef LITTLE_ENDIAN
		ByteOrder m_destinationByteOrder = ByteOrder_LittleEndian;
#else
		ByteOrder m_destinationByteOrder = ByteOrder_BigEndian;
#endif

	};
}
