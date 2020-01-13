#include "stdafx.h"
#include "..\Header\misTableRangeSelector.h"
#include "misApplicationSetting.h"
 

misTableRangeSelector::misTableRangeSelector(misImageingProperties imageProp, double minScalarRange, double maxScalarRange)
	:m_ImageProp(imageProp), m_MinScalarRange(minScalarRange), m_MaxScalarRange(maxScalarRange)
{

	misApplicationSetting* appSetting = misApplicationSetting::GetInstance();
	
		if (MRI == m_ImageProp.ImageModality)
		{
			m_TableRange.push_back(std::max(appSetting->GetDataUploadingSetting().m_MinMRIRange, minScalarRange) );
			m_TableRange.push_back(std::min(appSetting->GetDataUploadingSetting().m_MaxMRIRange, maxScalarRange));
		}
		else if (CT == imageProp.ImageModality)
		{
			const double boundingThresholSafty = 10.0;
			m_TableRange.push_back(std::max(appSetting->GetDataUploadingSetting().m_MinCTRange, minScalarRange) 
				- boundingThresholSafty);
			m_TableRange.push_back(std::min(appSetting->GetDataUploadingSetting().m_MaxCTRange, maxScalarRange) 
				+ boundingThresholSafty);
		}


	if (m_TableRange.size() == 0)
	{
		m_TableRange.push_back(minScalarRange);
		m_TableRange.push_back(maxScalarRange);
	}

 }

std::vector<double> misTableRangeSelector::GetRange()const
{
	return m_TableRange;
}
