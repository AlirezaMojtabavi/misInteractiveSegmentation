#pragma once
class ISegmentedObjectTransferFunction3D
{
public:
	virtual unsigned int GetTransferFunctionId() = 0;
	virtual std::vector<int> GetAllocationBytes() = 0 ;
};
