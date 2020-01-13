#include "stdafx.h"
#include "misShaderHeaderGeneratorforImageViewer.h"
#include "misImageSlicerMapper.h"


#define WRITE_TO_HEADER(x,condition)\
	if(condition)\
	m_GeneratedHeader <<"#define "<< x << std::endl;


misShaderHeaderGeneratorforImageViewer::misShaderHeaderGeneratorforImageViewer(
	std::vector<std::string> &planeNames,
	std::vector<misTextureViewingProperties> &GroupTextureViewingProperties,
	std::vector<ImageContainedTransferFuncs> &GroupImageContainedTFs) :
	m_planeNames(planeNames),
	m_GroupTextureViewingProperties(GroupTextureViewingProperties),
	m_GroupImageContainedTFs(GroupImageContainedTFs),
	m_isOldShaderUsed(false),
	m_GeneratedHeader("")
{

}


void misShaderHeaderGeneratorforImageViewer::ComposeHeader()
{
	m_GeneratedHeader.str("");

	int loopVarient = 0;
	if (sizeof(ImageContainedDataType) == sizeof(unsigned short))
		loopVarient = 6;


	for (int i = 0; i < m_planeNames.size(); i++)
	{
		if (m_planeNames[i] != "")
		{

			m_GeneratedHeader << "#define " << "GROUPS_NUM_" << (i + 2) << std::endl;
			WRITE_TO_HEADER(m_planeNames[i] + "VisiblityOfMT", m_GroupTextureViewingProperties[i].GetVisiblityOfMT());

			WRITE_TO_HEADER(m_planeNames[i] + "VisiblityofSegmentedImage", m_GroupTextureViewingProperties[i].GetVisiblityofSegmentedImage() & m_GroupImageContainedTFs[i][0].GetAssigned());
			WRITE_TO_HEADER(m_planeNames[i] + "VisiblityofFmriImage", m_GroupTextureViewingProperties[i].GetVisiblityofFmriImage());
			WRITE_TO_HEADER(m_planeNames[i] + "VisiblityOfColorMap", m_GroupTextureViewingProperties[i].GetVisiblityOfColorMap());

			if (!m_GroupTextureViewingProperties[i].GetVisiblityOfMT() &&
				!m_GroupTextureViewingProperties[i].GetVisiblityofSegmentedImage() &&
				!m_GroupTextureViewingProperties[i].GetVisiblityOfColorMap())
			{
				continue;
			}


			if (m_isOldShaderUsed == false)
			{
#pragma region NEW SHADER
				if ((m_GroupTextureViewingProperties[i].GetSegmentedImageID() > 0) &&
					(true == m_GroupTextureViewingProperties[i].GetVisiblityofSegmentedImage()))
				{
					GLboolean istexturecheck = glIsTexture(m_GroupTextureViewingProperties[i].GetSegmentedImageID());
					_ASSERT(istexturecheck == 1);
					_ASSERT(m_GroupTextureViewingProperties[i].GetSegmentedImageID() < 1000);
					if (istexturecheck)
					{

						auto imageContainedTFs = m_GroupImageContainedTFs[i];
						for (int j = 0; j < loopVarient/*imageContainedTFs.size()*/; j++)
						{
							if (j < m_GroupImageContainedTFs[i].size() && imageContainedTFs[j].GetAssigned())
							{
								GLboolean ispolydataTexturecheck = glIsTexture(imageContainedTFs[j].GetTfId());
								_ASSERT(ispolydataTexturecheck == 1);
								_ASSERT(imageContainedTFs[j].GetTfId() < 1000);

								if (ispolydataTexturecheck)
								{

									WRITE_TO_HEADER(ConvertSegmentedObjectIndexToString(i, j) + "isActive", true);

								}

							}
							else
							{
								WRITE_TO_HEADER(ConvertSegmentedObjectIndexToString(i, j) + "isActive", false);
							}
						}
					}

				}

#pragma endregion NEW SHADER
			}
			// Set FMRI Shader Variables
		}


	}



}

std::string misShaderHeaderGeneratorforImageViewer::ConvertSegmentedObjectIndexToString(int groupIndex, int objectIndex)
{
	if (groupIndex < 0 || objectIndex < 0)
		return "";

	std::ostringstream planeNum;
	planeNum << "GroupContainedColorMap_" << groupIndex + 1  << "_" << objectIndex + 1 << "_";
	return planeNum.str();
}

std::string misShaderHeaderGeneratorforImageViewer::GetHeader() const
{
	return m_GeneratedHeader.str();
}

void misShaderHeaderGeneratorforImageViewer::setOldShaderIsUsed(bool isUsed)
{
	m_isOldShaderUsed = isUsed;
}
