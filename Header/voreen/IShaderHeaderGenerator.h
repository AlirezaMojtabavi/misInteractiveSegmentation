#pragma once
#include "TransferFuncs3D.h"
#include "optionproperty.h"
#include "misCroppingDirectionInVR.h"

#ifndef ImageContainedDataType
#define  ImageContainedDataType unsigned short
#endif
namespace voreen
{
	class IShaderHeaderGenerator
	{
	public:
		virtual void ComposeHeader() = 0;
		virtual std::string GetHeader() const = 0;
		virtual void setVoreenGeneratedHeader(std::string) = 0;
		virtual void setCroppingDirectionInVR(misCroppingDirectionInVR) = 0;
		virtual void setNumOfVolumes(int) = 0;
	};
}