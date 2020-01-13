#pragma once
#include "ApplicationBusinessRules/ISingleVariableFunction.h"

MOCK_BASE_CLASS(MockSingleVariableFunction, ISingleVariableFunction)
{
	MOCK_CONST_METHOD(operator(), 1, double(double x), ParenthesisOperator);
};