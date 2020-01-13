#pragma once
#include "IArrayBinaryCodec.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockArrayBinaryCodecInt6, IArrayBinaryCodec<int, 6>)
	{
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const int array[6]));
		MOCK_CONST_METHOD(FromByteArray, 2, void(const ByteArray& byteArray, int array[6]));
	};

	MOCK_BASE_CLASS(MockArrayBinaryCodecDouble3, IArrayBinaryCodec<double, 3>)
	{
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const double array[3]));
		MOCK_CONST_METHOD(FromByteArray, 2, void(const ByteArray& byteArray, double array[3]));
	};
	
	MOCK_BASE_CLASS(MockArrayBinaryCodecDouble6, IArrayBinaryCodec<double, 6>)
	{
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const double array[6]));
		MOCK_CONST_METHOD(FromByteArray, 2, void(const ByteArray& byteArray, double array[6]));
	};
	
	MOCK_BASE_CLASS(MockArrayBinaryCodecFloat3, IArrayBinaryCodec<float, 3>)
	{
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const float array[3]));
		MOCK_CONST_METHOD(FromByteArray, 2, void(const ByteArray& byteArray, float array[3]));
	};

	MOCK_BASE_CLASS(MockArrayBinaryCodecDouble16, IArrayBinaryCodec<double, 16>)
	{
		MOCK_CONST_METHOD(ToByteArray, 1, std::shared_ptr<ByteArray>(const double array[16]));
		MOCK_CONST_METHOD(FromByteArray, 2, void(const ByteArray& byteArray, double array[16]));
	};

}

