#pragma once

#include "misOpenglTexture.h"

class misTransferFunctionTester
{
private:
	TransFuncIntensity* m_IntensityFunction;
public:

	double GetAvergae(misOpenglTexture* texture);
	misTransferFunctionTester(TransFuncIntensity* function);
	~misTransferFunctionTester(void);
};

