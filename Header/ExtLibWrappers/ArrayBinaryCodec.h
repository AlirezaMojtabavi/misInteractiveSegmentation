#pragma once

#include "IArrayBinaryCodec.h"

namespace parcast
{

	typedef std::vector<unsigned char> ByteArray;

	template <typename ElemType, int Size>
	class ArrayBinaryCodec : public IArrayBinaryCodec<ElemType, Size>
	{
	public:
		virtual std::shared_ptr<ByteArray> ToByteArray(const ElemType array[Size]) const override
		{
			auto arrayPtr = reinterpret_cast<const uint8_t*>(array);
			auto result = std::make_shared<ByteArray>(arrayPtr, arrayPtr + Size * sizeof ElemType);
			return result;
		}

		virtual void FromByteArray(const ByteArray& byteArray, ElemType array[Size]) const override
		{
			if (byteArray.size() != Size * sizeof ElemType)
				throw std::exception("Cannot fit source data into destination array; insufficient space.");
			std::memcpy(reinterpret_cast<uint8_t*>(array), byteArray.data(), byteArray.size());
		}
	};

}

