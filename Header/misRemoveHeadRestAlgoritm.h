#pragma once
#include "misAnalysisStudioTypes.h"
#include "misRegionGrowing.h"
#include "IImage.h"
#include "misitkImageTypedef.h"

class misRemoveHeadRestAlgoritm
{
	const int minimumNegativeGraylevelValue = 4999;
	const int shifGraylevelOutOfRange = 10000;

public:
	misRemoveHeadRestAlgoritm();


	void SetImage(std::shared_ptr<IImage>  inputImage);
	void AddSeed(const double *seedPosition);
	void ResetSeeds();
	void ResetSetting();	//ResetSeeds, ResetThreshold,upperThroshold is maximum value in Original Image::5000
	bool RestoreImage();	// RG result image to the original input image-->opposit of ApplyResultToImage:: -10,000
	void SetLowerThreshold(double lThreshold);
	bool StartRemoveHeadRest(std::vector<parcast::PointD3> seeds);	//start RG using by seed and lower threshold



private:
	vtkImageData*	m_outputImage;
	bool ApplyRGResultToImage(vtkImageData* rgOutput);	//selected pixels come from RG_Output  +10,000  to show in original image
	signed short*	m_BufferInputImage;
	misRegionGrowing m_RegionGrowing;
	misitkSeedListType	m_Seed;
	unsigned char*	m_RgOutputImage;
	double			m_UpperThreshold;
	double			m_LowerThreshold;
 
};