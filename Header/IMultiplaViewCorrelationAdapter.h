#pragma once

class IMultiplaViewCorrelationAdapter
{
public:
	virtual ~IMultiplaViewCorrelationAdapter() = default;
	virtual void SetViewPortTypeToMultiple() = 0;
	
};
