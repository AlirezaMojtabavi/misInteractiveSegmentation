#pragma once

#include "misitkImageTypedef.h"
#include "misSimplePointType.h"

class misApplicationSetting;
class IImage;
class IRegionGrowing;

enum misObjectSizeType;

class  misSurfaceSegmentation
{
	typedef std::vector<float>  SeedListValueType;

public:
	misSurfaceSegmentation(std::shared_ptr<IRegionGrowing> regionGrowing, double defaultObjectMargin);

	static void CalculationInThread(void* pParams);
	void SetObjectType(misObjectSizeType objectTypeSize);
	void RequestCancelSegmentation();
	void Calculation();
	void SurfaceSegmentationInitialize();
	void FillFGSeedValueList();
	void FillBGSeedValueList();
	void InsertFGSeed(misSimplePointType FGSeed);
	void InsertBGSeed(misSimplePointType BGSeed);
	void SetBGSeed(misSimplePointListType FGSeedList);
	void SetFGSeed(misSimplePointListType BGSeedList);
	void SetImage(std::shared_ptr<IImage> image);
	void AddSeed(misSimplePointType seed);
	void Reset();
	void SetLowerThreshold(PixelType lowert);
	void SetUpperThreshold(PixelType Uppert);
	void StartRegionGrowingBasedSegmentation();
	float* Equation(float a, float b, float c);
	float* CalculateThreshold(float Mean1, float Mean2, float Var1, float Var2);
	std::vector<float> CalculateMean(misSimplePointListType SeedList);
	misitkImageType::Pointer StartThresholdBasedSegmentation();
	bool  CalculateThresholds();
	void CalculateChangeThresholdRate();
	PixelType GetLowerThreshold();
	PixelType GetUpperThrehold();
	void ReleaseResource();
	SeedListValueType GetBGSeedList();
	SeedListValueType GetBGDarkSeedList();
	SeedListValueType GetBGLightSeedList();
	SeedListValueType GetFGSeedList();
	void IncreaseThreshold();
	void DecreaseThreshold();
	void ResetThreshold();
	void ReCalculateWithNewThreshold();
	void SetROIData(double* data);
	misSimplePointListType m_FGSeedList;
	misSimplePointListType m_BGSeedList;
	bool m_SetROI;
	bool PreMaxThreshold{};
	bool PreMinThreshold{};
	bool m_UseThreadForSegmentation{};
	bool m_NewSegmentationHasBeenDone{};
	float MaxFG{};
	float MinFG{};
	float FGMean{};
	float BGLightMean{};
	float BGDarkMean{};
	float FGVariance{};
	float BGLightVariance{};
	float BGDarkVariance{};
	float m_UpperThreshold{};
	float m_LowerThreshold{};
	float m_LeftIncreasingRate{};
	float m_LeftDecreasingRate{};
	float m_RightIncreasingRate{};
	float m_RightDecreasingRate{};
	std::shared_ptr<IRegionGrowing> GetRegionGrowing() const;
	void SetRegionGrowing(std::shared_ptr<IRegionGrowing> val);

private:
	
	inline bool CheckIndexValidity(misSimplePointType seedPosition);
	bool CalculateLowerThreshold();
	bool CalculateUpperThreshold();
	bool UpdateSeedsPositionInRegionGrowingFilter();
	float CalculateVariance2(SeedListValueType SeedList, float mean);
	float CalculateMean2(SeedListValueType SeedList);
	void ClearLists();


	std::shared_ptr<IRegionGrowing> m_RegionGrowing;
	misSimplePointListType m_FGSeedListWithNeighbors;
	SeedListValueType m_FGSeedValueList;
	SeedListValueType m_BGSeedValueList;
	SeedListValueType m_BGDarkValueList;
	SeedListValueType m_BGLightValueList;
	misitkImageType::Pointer m_ItkConverterdImage;
	misSimplePointType m_Seed;
	std::shared_ptr<IImage> m_Image;
	misSimplePointType m_NeighborHoodSpread;
	double m_DefaultObjectMargin = 0;
	int* m_ImageSize{};
	int m_ThresholdStep;
	double m_IncreasingRate;
	double m_DecreasingRate;
	int m_IncreasingStepNumber;
	int m_DeccreasingStepNumber;
	double m_WidgetData[6]{};
};