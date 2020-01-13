#include "StdaFx.h"
#include "misSurfaceSegmentation.h"

#include "misApplicationSetting.h"
#include "IImage.h"
#include "IRegionGrowing.h"

using namespace std;

misSurfaceSegmentation::misSurfaceSegmentation(std::shared_ptr<IRegionGrowing> regionGrowing,
                                               double defaultObjectMargin)
	: m_RegionGrowing(regionGrowing),
	m_DefaultObjectMargin(defaultObjectMargin)
{
	SurfaceSegmentationInitialize();
	m_SetROI = false;
	m_ThresholdStep = 15;
	m_IncreasingRate = 0.0;
	m_DecreasingRate = 0.0;
	m_IncreasingStepNumber = 0;
	m_DeccreasingStepNumber = 0;
}

void misSurfaceSegmentation::SetImage(std::shared_ptr<IImage> image)
{
	m_Image = image;
	m_ImageSize = m_Image->GetRawImageData()->GetDimensions();
}

void misSurfaceSegmentation::InsertFGSeed(misSimplePointType FGSeed)
{
	if (FGSeed.validity == true)
	{
		m_FGSeedList.push_back(FGSeed);
	}
}

void misSurfaceSegmentation::InsertBGSeed(misSimplePointType BGSeed)
{
	if (BGSeed.validity == true)
	{
		m_BGSeedList.push_back(BGSeed);
	}
}

void misSurfaceSegmentation::SetBGSeed(misSimplePointListType BGSeedList)
{
	m_BGSeedList = BGSeedList;
}

void misSurfaceSegmentation::SetFGSeed(misSimplePointListType FGSeedList)
{
	m_FGSeedList = FGSeedList;
}

void misSurfaceSegmentation::FillFGSeedValueList()
{
	float tempValue;
	int tSize;
	misSimplePointType tempIndex1;
	misSimplePointType tempIndex2;
	m_FGSeedValueList.clear();
	m_FGSeedListWithNeighbors.clear();
	tSize = m_FGSeedList.size();
	for (int i = 0; i < tSize; i++)
	{
		tempIndex1 = m_FGSeedList[i];

		for (int i = -1 * m_NeighborHoodSpread[0]; i <= m_NeighborHoodSpread[0]; i++)
		{
			for (int j = -1 * m_NeighborHoodSpread[1]; j <= m_NeighborHoodSpread[1]; j++)
			{
				for (int k = -1 * m_NeighborHoodSpread[2]; k <= m_NeighborHoodSpread[2]; k++)
				{
					tempIndex2[0] = tempIndex1[0] + i;
					tempIndex2[1] = tempIndex1[1] + j;
					tempIndex2[2] = tempIndex1[2] + k;
					tempIndex2.validity = tempIndex1.validity;
					if (true == CheckIndexValidity(tempIndex2))
					{
						m_FGSeedListWithNeighbors.push_back(tempIndex2);
						tempValue = m_Image->GetRawImageData()->GetScalarComponentAsFloat(tempIndex2[0], tempIndex2[1], tempIndex2[2], 0);
						m_FGSeedValueList.push_back(tempValue);
					}
				}
			}
		}
	}
	SeedListValueType::iterator maxValue;
	SeedListValueType::iterator minValue;
	maxValue = std::max_element(m_FGSeedValueList.begin(), m_FGSeedValueList.end());
	MaxFG = *maxValue;
	minValue = std::min_element(m_FGSeedValueList.begin(), m_FGSeedValueList.end());
	MinFG = *minValue;
}

void misSurfaceSegmentation::FillBGSeedValueList()
{
	float tempValue;
	int tSize;
	misSimplePointType tempIndex1;
	misSimplePointType tempIndex2;
	m_BGSeedValueList.clear();
	tSize = m_BGSeedList.size();

	for (int i = 0; i < tSize; i++)
	{
		tempIndex1 = m_BGSeedList[i];

		for (int k = -3; k <= 3; k++)
		{
			for (int l = -3; l <= 3; l++)
			{
				for (int m = -1; m <= 1; m++)
				{
					tempIndex2[0] = tempIndex1[0] + k;
					tempIndex2[1] = tempIndex1[1] + l;
					tempIndex2[2] = tempIndex1[2] + m;
					tempIndex2.validity = tempIndex1.validity;

					if (true == CheckIndexValidity(tempIndex2))
					{
						tempValue = m_Image->GetRawImageData()->GetScalarComponentAsFloat(tempIndex2[0], tempIndex2[1], tempIndex2[2], 0);
						m_BGSeedValueList.push_back(tempValue);
					}
				}
			}
		}
	}
}

std::vector<float> misSurfaceSegmentation::CalculateMean(misSimplePointListType SeedList)
{

	float tempValue = 0;
	float tempMean = 0;
	float Mean = 0;
	std::vector<float> tempMeanList;
	misSimplePointType tempPixel;
	misSimplePointType tempPixel2;
	int SeedSize = SeedList.size();
	//calculate Mean
	for (int i = 0; i < SeedSize; i++)
	{
		if (SeedList[i].validity == true)
		{
			tempPixel = SeedList[i];
			tempValue = 0;
			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					for (int m = -1; m <= 1; m++)
					{
						tempPixel2[0] = tempPixel[0] + k;
						tempPixel2[1] = tempPixel[1] + l;
						tempPixel2[2] = tempPixel[2] + m;
						// to check it be in the image region
						if (true == CheckIndexValidity(tempPixel2))
						{
							tempValue = tempValue + m_Image->GetRawImageData()->GetScalarComponentAsFloat(tempPixel2[0], tempPixel2[1], tempPixel2[2], 0);
						}
					}
				}
			}
		}
		tempMean = tempValue / 27;
		tempMeanList.push_back(tempMean);
	}
	return tempMeanList;
}

bool misSurfaceSegmentation::CalculateLowerThreshold()
{
	int tSize = m_BGSeedValueList.size();
	m_BGDarkValueList.clear();
	for (int i = 0; i < tSize; i++)
	{
		if (m_BGSeedValueList[i] < MinFG)
		{
			m_BGDarkValueList.push_back(m_BGSeedValueList[i]);
		}
	}
	FGMean = CalculateMean2(m_FGSeedValueList);
	FGVariance = CalculateVariance2(m_FGSeedValueList, FGMean);
	BGDarkMean = CalculateMean2(m_BGDarkValueList);
	BGDarkVariance = CalculateVariance2(m_BGDarkValueList, BGDarkMean);
	auto thresholds = CalculateThreshold(FGMean, BGDarkMean, FGVariance, BGDarkVariance);
	float lowthreshold;
	if (BGDarkMean == NULL)
	{
		PreMinThreshold = true;
		float MINTHreshold = 0;
		lowthreshold = MINTHreshold;
	}
	else
	{
		float tmin = min(FGMean - FGVariance, BGDarkMean);
		float tmax = max(FGMean - FGVariance, BGDarkMean);
		if (thresholds[0] > tmin && thresholds[0] < tmax)
		{
			if (thresholds[1] > tmin && thresholds[1] < tmax)
			{
				if (thresholds[0] < thresholds[1])
					lowthreshold = thresholds[0];
				else
					lowthreshold = thresholds[1];
			}
			else
			{
				lowthreshold = thresholds[0];
			}
		}
		else if (thresholds[1] > tmin && thresholds[1] < tmax)
		{
			lowthreshold = thresholds[1];
		}
		else
		{
			lowthreshold = (tmin + tmax) / 2;
		}
	}
	m_LowerThreshold = lowthreshold;
	if ((m_LowerThreshold >= BGDarkMean) && (m_LowerThreshold <= FGMean))
	{
		return true;
	}

	return false;
}

bool misSurfaceSegmentation::CalculateUpperThreshold()
{
	int tSize = m_BGSeedValueList.size();
	float validRange = MaxFG - MinFG;
	m_BGLightValueList.clear();
	for (int i = 0; i < tSize; i++)
	{
		if (m_BGSeedValueList[i] > MaxFG)
		{
			m_BGLightValueList.push_back(m_BGSeedValueList[i]);
		}
	}

	FGMean = CalculateMean2(m_FGSeedValueList);
	FGVariance = CalculateVariance2(m_FGSeedValueList, FGMean);
	BGLightMean = CalculateMean2(m_BGLightValueList);
	BGLightVariance = CalculateVariance2(m_BGLightValueList, BGLightMean);
	float upthreshold;
	if (BGLightMean == NULL)
	{
		PreMaxThreshold = true;
		float MAXTHreshold = 4000;
		upthreshold = MAXTHreshold;
	}
	else
	{
		auto thresholds = CalculateThreshold(BGLightMean, FGMean, BGLightVariance, FGVariance);
		float tmin = min(FGMean + FGVariance, BGLightMean);
		float tmax = max(FGMean + FGVariance, BGLightMean);
		if (thresholds[0] > tmin && thresholds[0] < tmax)
		{
			if (thresholds[1] > tmin && thresholds[1] < tmax)
			{
				if (thresholds[0] > thresholds[1])
					upthreshold = thresholds[0];
				else
					upthreshold = thresholds[1];
			}
			else
			{
				upthreshold = thresholds[0];
			}
		}
		else if (thresholds[1] > tmin && thresholds[1] < tmax)
		{
			upthreshold = thresholds[1];
		}
		else
		{
			upthreshold = (tmin + tmax) / 2;
		}
	}

	m_UpperThreshold = upthreshold;
	if ((m_UpperThreshold <= BGLightMean) && (m_UpperThreshold >= FGMean))
	{
		return true;
	}

	return false;
}

void misSurfaceSegmentation::StartRegionGrowingBasedSegmentation()
{
	WaitForSingleObject(m_RegionGrowing->GetMutex(), INFINITE);
	bool runInDiffThread = m_UseThreadForSegmentation;
	ReleaseMutex(m_RegionGrowing->GetMutex());
	if (false == runInDiffThread)
	{
		Calculation();
	}
	else
	{
		// use thread for uploading
		_beginthread(misSurfaceSegmentation::CalculationInThread, 0, this); // create thread
		// in updateStatus new flag has been proceed
	}
}

misitkImageType::Pointer misSurfaceSegmentation::StartThresholdBasedSegmentation()
{
	typedef   float           PixelType;
	const     unsigned int    Dimension = 3;
	typedef itk::Image< PixelType, Dimension >  ImageType;
	typedef itk::ThresholdImageFilter<ImageType > ThresholdFilterType;
	auto thresholdFiler = ThresholdFilterType::New();
	thresholdFiler->SetInput(m_ItkConverterdImage);
	thresholdFiler->ThresholdAbove(255);
	thresholdFiler->Update();
	ImageType::Pointer SegmentedImage;
	SegmentedImage = thresholdFiler->GetOutput();
	return SegmentedImage;
}

float* misSurfaceSegmentation::Equation(float a, float b, float c)
{
	float* x = new float[2];
	float x1 = 0;
	float x2 = 0;
	float delta = b*b - 4 * a*c;
	if (delta < 0)
	{
		return 0;
	}
	if (delta == 0)
	{
		x[0] = -b / (2 * a);
		x[1] = -b / (2 * a);
	}
	if (delta > 0)
	{
		x1 = (-b + sqrt(delta)) / (2 * a);
		x2 = (-b - sqrt(delta)) / (2 * a);
		x[0] = x1;
		x[1] = x2;
	}
	return x;
}

float*  misSurfaceSegmentation::CalculateThreshold(float Mean1, float Mean2, float Var1, float Var2)
{
	float* threshold;
	if ((Var2 <= .1) || (Var1 <= 0.1))
	{
		threshold = new float[2];
		threshold[0] = (Mean1 + Mean2) / 2;
		threshold[1] = threshold[0];
		return threshold;
	}
	float P2OP1 = 0.5;
	float a = Var1 - Var2;
	float b = (2 * Mean1*Var2) - (2 * Mean2*Var1);
	float c = Var1*Var2*(log(P2OP1*(Var1 / Var2))) - (Var2*Mean1*Mean1) + (Var1*Mean2*Mean2);
	threshold = Equation(a, b, c);
	return threshold;
}

float misSurfaceSegmentation::CalculateVariance2(SeedListValueType SeedList, float mean)
{
	int tSize = SeedList.size();
	float tValue = 0;
	float variance;
	for (int i = 0; i < tSize; i++)
	{
		tValue = tValue + pow((SeedList[i] - mean), 2);
	}
	tValue = tValue / (tSize - 1);
	variance = sqrt(tValue);
	if (tSize == 0)
	{
		return NULL;
	}
	return variance;
}

float misSurfaceSegmentation::CalculateMean2(SeedListValueType SeedList)
{
	int tSize = SeedList.size();
	float tValue = 0;
	float mean;
	for (int i = 0; i < tSize; i++)
	{
		tValue = tValue + SeedList[i];
	}
	if (tSize == 0)
	{
		return NULL;
	}
	mean = tValue / tSize;
	return mean;
}

void misSurfaceSegmentation::SetLowerThreshold(PixelType lower)
{
	m_LowerThreshold = lower;
}

void misSurfaceSegmentation::SetUpperThreshold(PixelType Uppert)
{
	m_UpperThreshold = Uppert;
}

void misSurfaceSegmentation::AddSeed(misSimplePointType seed)
{
	if (seed.validity == true)
	{
		m_RegionGrowing->AddSeed(seed[0], seed[1], seed[2]);
	}
}

void misSurfaceSegmentation::Reset()
{
	m_RegionGrowing->ClearSeeds();
	ClearLists();
}

void misSurfaceSegmentation::ClearLists()
{
	m_FGSeedList.clear();
	m_FGSeedListWithNeighbors.clear();
	m_BGSeedList.clear();
	m_FGSeedValueList.clear();
	m_BGSeedValueList.clear();
	m_BGDarkValueList.clear();
	m_BGLightValueList.clear();
	MaxFG = -1;
	MinFG = -1;
	FGMean = -1;
	BGLightMean = -1;
	BGDarkMean = -1;
	FGVariance = -1;
	BGLightVariance = -1;
	BGDarkVariance = -1;
	m_UpperThreshold = -1;
	m_LowerThreshold = -1;
}

bool misSurfaceSegmentation::UpdateSeedsPositionInRegionGrowingFilter()
{
	int tsize = 0;
	m_RegionGrowing->ClearSeeds();
	tsize = m_FGSeedListWithNeighbors.size();
	for (int i = 0; i < tsize; i++)
	{
		m_RegionGrowing->AddSeed(m_FGSeedListWithNeighbors[i][0], m_FGSeedListWithNeighbors[i][1], m_FGSeedListWithNeighbors[i][2]);
	}
	if (0 == tsize)
	{
		return false;
	}

	return true;
};

bool  misSurfaceSegmentation::CalculateThresholds()
{
	FillBGSeedValueList();
	FillFGSeedValueList();
	bool res3 = CalculateLowerThreshold();
	bool res4 = CalculateUpperThreshold();
	CalculateChangeThresholdRate();
	bool res5 = UpdateSeedsPositionInRegionGrowingFilter();
	bool finalRes = (res3 || res4) * res5;
	return finalRes;
}

PixelType misSurfaceSegmentation::GetLowerThreshold()
{
	return m_RegionGrowing->GetLowerThreshold();
}

PixelType misSurfaceSegmentation::GetUpperThrehold()
{
	return m_RegionGrowing->GetHigherThreshold();
}

void misSurfaceSegmentation::SetObjectType(misObjectSizeType objectTypeSize)
{
	switch (objectTypeSize)
	{
	case NarrowObject:
		m_NeighborHoodSpread[0] = 0;
		m_NeighborHoodSpread[1] = 0;
		m_NeighborHoodSpread[2] = 0;
		break;
	case MediumObject:
		m_NeighborHoodSpread[0] = 1;
		m_NeighborHoodSpread[1] = 1;
		m_NeighborHoodSpread[2] = 1;
		break;
	case BigObject:
		m_NeighborHoodSpread[0] = 2;
		m_NeighborHoodSpread[1] = 2;
		m_NeighborHoodSpread[2] = 1;
		break;
	}
}

bool misSurfaceSegmentation::CheckIndexValidity(misSimplePointType seedPosition)
{
	if (seedPosition.validity == false)
	{
		return false;
	}
	if ((seedPosition[0] >= 0) && (seedPosition[1] >= 0) && (seedPosition[2] >= 0))
	{
		if ((seedPosition[0] <= m_ImageSize[0]) && (seedPosition[1] <= m_ImageSize[1]) && (seedPosition[2] <= m_ImageSize[2]))
		{
			return true;
		}
	}
	cout << " \n Invalid Seed  Position " << ":" << seedPosition[0] << "," << seedPosition[1] << "," << seedPosition[2] << std::ends;
	return true;
}

void misSurfaceSegmentation::RequestCancelSegmentation()
{
	m_RegionGrowing->RequestCancelSegmentation();
}

void misSurfaceSegmentation::Calculation()
{
	m_RegionGrowing->SetImage(m_Image->GetRawImageData());
	m_RegionGrowing->SetHigherThreshold(m_UpperThreshold);
	m_RegionGrowing->SetLowerThreshold(m_LowerThreshold);
	if (m_SetROI == true)
	{
		double *spacing = m_Image->GetRawImageData()->GetSpacing();
		m_RegionGrowing->SetMaximumObjectValidity(m_WidgetData);
		m_RegionGrowing->LimitBoundaryPosition(spacing);
		m_RegionGrowing->UpdateMaximumObjectValidityWithROI();
	}
	else if (m_SetROI == false)
	{
		m_RegionGrowing->ResetMaximumObjectValidRange();
		m_RegionGrowing->UpdateMaximumObjectValidityWithoutROI();
	}
	m_RegionGrowing->SetMargineValue(misMarginalRegion);
	m_RegionGrowing->ExtractBorderOff();
	m_RegionGrowing->SetDistanceFromMargine(m_DefaultObjectMargin);
	bool RGres = m_RegionGrowing->Calculation();
	WaitForSingleObject(m_RegionGrowing->GetMutex(), INFINITE);
	m_NewSegmentationHasBeenDone = true;
	ReleaseMutex(m_RegionGrowing->GetMutex());
}

void misSurfaceSegmentation::CalculationInThread(void* pParams)
{
	auto self = reinterpret_cast <misSurfaceSegmentation*> (pParams);
	if (self)
		self->Calculation();
}

void misSurfaceSegmentation::SurfaceSegmentationInitialize()
{
	m_Image = NULL;
	m_RegionGrowing->SetThresholdChecking(true);
	m_IncreasingRate = 0.0;
	m_DecreasingRate = 0.0;
	m_IncreasingStepNumber = 0;
	m_DeccreasingStepNumber = 0;
	m_NewSegmentationHasBeenDone = false;
	SetObjectType(MediumObject);
}

void misSurfaceSegmentation::ReleaseResource()
{
	m_NewSegmentationHasBeenDone = false;
}

misSurfaceSegmentation::SeedListValueType misSurfaceSegmentation::GetBGSeedList()
{
	return m_BGSeedValueList;
}

misSurfaceSegmentation::SeedListValueType misSurfaceSegmentation::GetBGDarkSeedList()
{
	return m_BGDarkValueList;
}

misSurfaceSegmentation::SeedListValueType misSurfaceSegmentation::GetBGLightSeedList()
{
	return m_BGLightValueList;
}

misSurfaceSegmentation::SeedListValueType misSurfaceSegmentation::GetFGSeedList()
{
	return m_FGSeedValueList;
}

void misSurfaceSegmentation::IncreaseThreshold()
{
	m_IncreasingStepNumber++;
	ReCalculateWithNewThreshold();
}

void misSurfaceSegmentation::DecreaseThreshold()
{
	m_DeccreasingStepNumber++;
	ReCalculateWithNewThreshold();
}

void misSurfaceSegmentation::ReCalculateWithNewThreshold()
{
	int diff = m_IncreasingStepNumber - m_DeccreasingStepNumber;
	if ((diff > m_ThresholdStep) || (diff < (-1 * m_ThresholdStep)))
	{
		m_RegionGrowing->RequestCancelSegmentation();
		WaitForSingleObject(m_RegionGrowing->GetMutex(), INFINITE);
		m_NewSegmentationHasBeenDone = true;
		ReleaseMutex(m_RegionGrowing->GetMutex());
		return;
	}
	float newUpperThreshold = m_UpperThreshold;
	float newLowerThreshold = m_LowerThreshold;
	if (diff >= 1)
	{
		newUpperThreshold = m_UpperThreshold + (m_RightIncreasingRate* diff);
		newLowerThreshold = m_LowerThreshold - (m_LeftIncreasingRate* diff);
	}
	else if (diff <= -1)
	{
		newUpperThreshold = m_UpperThreshold - (m_RightDecreasingRate* abs(diff));
		newLowerThreshold = m_LowerThreshold + (m_LeftDecreasingRate* abs(diff));
	}
	else if (diff == 0)
	{
		newUpperThreshold = m_UpperThreshold;
		newLowerThreshold = m_LowerThreshold;
	}
	UpdateSeedsPositionInRegionGrowingFilter();
	if (m_SetROI == true)
	{
		auto spacing = m_Image->GetRawImageData()->GetSpacing();
		m_RegionGrowing->SetMaximumObjectValidity(m_WidgetData);
		m_RegionGrowing->LimitBoundaryPosition(spacing);
		m_RegionGrowing->UpdateMaximumObjectValidityWithROI();
	}
	else if (m_SetROI == false)
		m_RegionGrowing->UpdateMaximumObjectValidityWithoutROI();

	m_RegionGrowing->SetImage(m_Image->GetRawImageData());
	m_RegionGrowing->SetHigherThreshold(newUpperThreshold);
	m_RegionGrowing->SetLowerThreshold(newLowerThreshold);

	bool RGres = m_RegionGrowing->Calculation();
	WaitForSingleObject(m_RegionGrowing->GetMutex(), INFINITE);
	m_NewSegmentationHasBeenDone = true;
	ReleaseMutex(m_RegionGrowing->GetMutex());
	if (RGres)
	{
		m_RegionGrowing->ApplyMarginalBorder();
	}
}

void misSurfaceSegmentation::CalculateChangeThresholdRate()
{
	m_LeftIncreasingRate = abs(m_LowerThreshold - min(BGDarkMean, m_LowerThreshold)) / m_ThresholdStep;
	m_LeftDecreasingRate = abs(max(FGMean - FGVariance, m_LowerThreshold) - m_LowerThreshold) / m_ThresholdStep;
	m_RightIncreasingRate = abs(max(BGLightMean, m_UpperThreshold) - m_UpperThreshold) / m_ThresholdStep;
	m_RightDecreasingRate = abs(m_UpperThreshold - min(m_UpperThreshold, FGMean + FGVariance)) / m_ThresholdStep;
}

void misSurfaceSegmentation::ResetThreshold()
{
	m_DeccreasingStepNumber = 0;
	m_IncreasingStepNumber = 0;
	ReCalculateWithNewThreshold();
}

void misSurfaceSegmentation::SetROIData(double* data)
{
	if (data)
	{
		m_WidgetData[0] = data[0];
		m_WidgetData[1] = data[1];
		m_WidgetData[2] = data[2];
		m_WidgetData[3] = data[3];
		m_WidgetData[4] = data[4];
		m_WidgetData[5] = data[5];
	}
}

std::shared_ptr<IRegionGrowing> misSurfaceSegmentation::GetRegionGrowing() const
{
	return m_RegionGrowing;
}

void misSurfaceSegmentation::SetRegionGrowing(std::shared_ptr<IRegionGrowing> val)
{
	m_RegionGrowing = val;
}