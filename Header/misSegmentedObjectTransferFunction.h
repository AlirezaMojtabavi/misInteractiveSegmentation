#pragma once

class misSegmentedObjectTransferFunction
{

public:
	misSegmentedObjectTransferFunction();

	void SetTf(std::shared_ptr<TransFuncIntensity> tf);
	std::shared_ptr<TransFuncIntensity>  GetTf()const ;
	GLuint GetTfId();
	std::vector<int> allocatedByte;
	bool GetAssigned();
	void Reset();

private:
	std::shared_ptr<TransFuncIntensity> m_Tf;
	bool m_IDAssigned;
};