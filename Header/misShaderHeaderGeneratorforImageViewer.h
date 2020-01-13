#pragma once

#include "IShaderHeaderGenerator2D.h"
#include "misTextureViewingProperties.h"
#include "misVideoStruct.h"
#include "misSegmentedObjectTransferFunction.h"

typedef std::vector<misSegmentedObjectTransferFunction> ImageContainedTransferFuncs;
class misShaderHeaderGeneratorforImageViewer:public IShaderHeaderGenerator2D
{
public:
	misShaderHeaderGeneratorforImageViewer(std::vector<std::string> &,
		std::vector<misTextureViewingProperties> &,
		std::vector<ImageContainedTransferFuncs> &);
	virtual void ComposeHeader() override;
	virtual std::string GetHeader() const override;
	virtual void setOldShaderIsUsed(bool) override;

private:
	std::stringstream m_GeneratedHeader;
	std::vector<std::string> &m_planeNames;
	std::vector<misTextureViewingProperties> &m_GroupTextureViewingProperties;
	std::vector<ImageContainedTransferFuncs> &m_GroupImageContainedTFs;
	bool m_isOldShaderUsed;

	std::string ConvertSegmentedObjectIndexToString( int groupIndex , int objectIndex );

};