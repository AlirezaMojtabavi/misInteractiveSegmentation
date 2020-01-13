#pragma once

namespace parcast
{

	typedef std::vector<unsigned char> ByteArray;

	template <typename ElemType, int Size>
	class IArrayBinaryCodec
	{
	public:
		virtual std::shared_ptr<ByteArray> ToByteArray(const ElemType array[Size]) const = 0;
		virtual void FromByteArray(const ByteArray& byteArray, ElemType array[Size]) const = 0;
	};

}
