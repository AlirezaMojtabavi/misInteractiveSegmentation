#pragma once
class TransFuncIntensity;
struct SegmentedObjectTransferFunction3D
{
	std::vector<int> allocatedByte;
	std::shared_ptr<TransFuncIntensity> transferFunction;

	SegmentedObjectTransferFunction3D()
	{
		transferFunction = 0;
		allocatedByte.clear();
	}
	void operator = (SegmentedObjectTransferFunction3D right)
	{
		this->transferFunction = right.transferFunction;
		this->allocatedByte = right.allocatedByte;
	}
};
typedef std::vector<SegmentedObjectTransferFunction3D> ImageContainedTransferFuncs3D;