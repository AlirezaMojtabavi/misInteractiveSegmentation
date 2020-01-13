#pragma once

#include "IVtkTransMatBinaryCodec.h"

namespace parcast
{

	class VtkTransMatBinaryCodec : public IVtkTransMatBinaryCodec
	{
	public:
		virtual std::shared_ptr<ByteArray> TransToByteArray(vtkSmartPointer<vtkTransform> trans) const override;
		virtual vtkSmartPointer<vtkTransform> ByteArrayToTrans(const ByteArray& byteArray) const override;
	};

}


