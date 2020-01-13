#pragma once

class ISingleVariableFunction
{
public:
	virtual double operator()(double x) const = 0;
};