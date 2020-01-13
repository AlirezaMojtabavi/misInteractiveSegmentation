#include "stdafx.h"
#include "misVolumeThresholdSetting.h"
#include "misApplicationSetting.h"


misVolumeThresholdSetting::misVolumeThresholdSetting(std::shared_ptr<IImage> image)
	:m_Image(image)
{
}

 
double misVolumeThresholdSetting::GetObjectThresholdBasedNormalizedThreshold(const mis3DModelTypes obJcetType
	, double normalizedThreshold)
{
	double threshold = -1;

	ObjectRangeListTypdef defalutObjectsRange =
		misApplicationSetting::GetInstance()->m_VisulaizationSetting.DefaultRangeList;
	misObjectRangeStr  currentObjectRange;
	misImageDataModality imageModality = m_Image->GetImageModality();

	for (int i = 0; i < defalutObjectsRange.size(); i++)
	{
		currentObjectRange = defalutObjectsRange[i];

		if ((currentObjectRange.ImageModality == imageModality) && (currentObjectRange.ModelType == obJcetType))
		{
			double range = currentObjectRange.ValidRange[1] - currentObjectRange.ValidRange[0];
			threshold = currentObjectRange.ValidRange[0] + normalizedThreshold * range;

			return threshold;
		}
	}
	misObjectRangeStr  defaultObjectRange;
	// current object range filled with default values
	double range = defaultObjectRange.ValidRange[1] - defaultObjectRange.ValidRange[0];
	threshold = defaultObjectRange.ValidRange[0] + normalizedThreshold * range;

	cout << "\n   Error:    Unable to find set value for this type of image";
	cout << "\n   Information: current object Threshold ( calculate Based on defalut values: " << threshold << ends;

	return threshold;
}

double misVolumeThresholdSetting::GetNormalizedObjectThresholdBasedOnThreshold(const mis3DModelTypes obJcetType,
	double threshold)
{
	double norThreshold = -1;

	ObjectRangeListTypdef defalutObjectsRange =
		misApplicationSetting::GetInstance()->m_VisulaizationSetting.DefaultRangeList;
	misObjectRangeStr     currentObjectRange;
	misImageDataModality  imageModality = m_Image->GetImageModality();

	for (int i = 0; i < defalutObjectsRange.size(); i++)
	{
		currentObjectRange = defalutObjectsRange[i];

		if ((currentObjectRange.ImageModality == imageModality) && (currentObjectRange.ModelType == obJcetType))
		{
			double range = currentObjectRange.ValidRange[1] - currentObjectRange.ValidRange[0];
			norThreshold = (threshold - currentObjectRange.ValidRange[0]) / range;
			if ((norThreshold < 0) || (norThreshold > 1))
			{
				//norThreshold = .5;
				cout << "\n    Error: Normalized threshold caluculation is wrong: " << threshold << ends;
			}
			else
			{
				cout << "\n   Information: current object Threshold : " << threshold << ends;
			}
			return norThreshold;
		}
	}
	misObjectRangeStr  defaultObjectRange;
	// current object range filled with default valuse
	double range = defaultObjectRange.ValidRange[1] - defaultObjectRange.ValidRange[0];
	norThreshold = defaultObjectRange.ValidRange[0] + threshold * range;

	cout << "\n   Error:    Unable to find set value for this type of image";
	if ((norThreshold < 0) || (norThreshold > 1))
	{
		//norThreshold = .5;
		cout << "\n    Error: Normalized threshold caluculation is wrong: " << norThreshold << ends;
	}
	else
	{
		cout << "\n   Information: current object Threshold ( calculate Based on defalut values: " << norThreshold << ends;
	}

	return norThreshold;
}

double misVolumeThresholdSetting::GetDefaultVolumeThreshold(const mis3DModelTypes obJcetType)
{
	double defaultThreshold = 0;;

	misImageDataModality  imageModality = m_Image->GetImageModality();
	auto appSetting = misApplicationSetting::GetInstance();
	if (CT == imageModality)
	{
		if (misSkin == obJcetType)
		{
			defaultThreshold = appSetting->m_VisulaizationSetting.SkinThresholdForCT;
		}
		else if (misBone == obJcetType)
		{
			defaultThreshold = appSetting->m_VisulaizationSetting.BoneThresholdForCT;
		}
	}
	else if (MRI == imageModality)
	{
		if (misSkin == obJcetType)
		{
			defaultThreshold = appSetting->m_VisulaizationSetting.SkinThresholdForMRI;
		}
	}
	return defaultThreshold;
}