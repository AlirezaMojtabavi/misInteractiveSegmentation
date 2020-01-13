#pragma once

#ifndef ImageContainedDataType
#define  ImageContainedDataType unsigned short
#endif

class IShaderHeaderGenerator2D
{
public:
	virtual void ComposeHeader() = 0;
	virtual std::string GetHeader() const = 0;
	virtual void setOldShaderIsUsed(bool) = 0;
};
