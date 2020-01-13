#pragma once

#include "IVtkTransMatBinaryCodec.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVtkTransMatBinaryCodec, IVtkTransMatBinaryCodec)
	{
		MOCK_CONST_METHOD(TransToByteArray, 1, std::shared_ptr<ByteArray>(vtkSmartPointer<vtkTransform> trans));
		MOCK_CONST_METHOD(ByteArrayToTrans, 1, vtkSmartPointer<vtkTransform> (const ByteArray& BytArray));
	};

}
