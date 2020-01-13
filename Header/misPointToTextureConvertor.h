#pragma once

#include "IPointToTextureConvertor.h"
#include "misROI.h"

// The class misPointToTextureConvertor get a vector of points by using a TransferFunc class convert the pixel data to a 1d 
// texture for using this texture as a function on GPU interpolation archives directly by GPU
class misPointToTextureConvertor : public IPointToTextureConvertor
{
public:
	// IPointToTextureConvertor interface:
	virtual void SetPoints(const std::vector<itk::Point<double, 3>>& points) override;
	virtual void SetImageDimensions(const misROI& roi) override;
	virtual GLuint GetTexture() const override;

private:
	misROI m_ImageDims;
	std::shared_ptr<TransFunc> m_TransFunction; // used for converting pixed data to texture
};

