#pragma once

namespace parcast
{

	typedef std::vector<unsigned char> ByteArray;
	
	class IVtkTransMatBinaryCodec
	{
	public:
		virtual std::shared_ptr<ByteArray> TransToByteArray(vtkSmartPointer<vtkTransform> trans) const = 0;
		virtual vtkSmartPointer<vtkTransform> ByteArrayToTrans(const ByteArray& byteArray) const = 0;
	};

}
