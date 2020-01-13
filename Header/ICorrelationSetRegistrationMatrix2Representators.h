#pragma once
#include "CorrelationRegistrationState.h"

namespace parcast
{
class ICorrelationSetRegistrationMatrix2Representators
{
public:
	virtual ~ICorrelationSetRegistrationMatrix2Representators() = default;
	virtual void SetRegistrationMatrix2Representators(std::shared_ptr<CorrelationRegistrationState>) = 0;
private:
};
	
}
