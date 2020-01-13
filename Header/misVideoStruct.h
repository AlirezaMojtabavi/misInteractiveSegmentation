#pragma once
#include "misSimplePointType.h"
struct misVideoStruct
{
	int Extent[6];
	double Spacing[3];
};

struct misVideoTextureProperties
{
	std::vector<misSimplePointType> planePints;
	std::vector<misSimplePointType> texturePoints;

private:
	bool VideoTexturePropValidity;
	bool VideoStarted;
	GLuint VideoTextureId;
	GLuint VideoTransferFunctionId;

public:
	misVideoTextureProperties()
	{
		Reset();
	}

	void Reset() 
	{
		this->VideoTextureId = 0;
		this->planePints.clear();
		this->texturePoints.clear();
		this->VideoTexturePropValidity = false;
		this->VideoStarted = false;
	}

	void SetVTextureID(GLuint id)
	{
		this->VideoTextureId = id;
		this->VideoTexturePropValidity = true;
	}

	void SetVTransferFuncID(GLuint id)
	{
		if (VideoTexturePropValidity)
		{
			this->VideoTransferFunctionId = id;
		}
	}
	void SetVideoStarted(bool val)
	{
		VideoStarted = val;
	}
	bool IsVAlidate()
	{
		return VideoTexturePropValidity;
	}
	bool IsVideoStarted ()
	{
		return VideoStarted;
	}
	GLuint GetVTextureID()
	{
		return VideoTextureId;
	}
	GLuint GetVTransferFuncID()
	{
		return VideoTransferFunctionId;
	}

};