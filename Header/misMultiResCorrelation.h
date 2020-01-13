#ifndef _misMultiResCorrelation_
#define _misMultiResCorrelation_

#include "misObject.h"
#include "RecursivePyramidFilter.h"
#include "MultiResolutionRegistration.h"

class  misMultiResCorrelation : public misOldObject
{
private:

	misMultiResCorrelation();
	/*itk::Image< float , 3 >* StartCorrelation(string ParameterFileName);*/
public:
	typedef itk::RecursivePyramidFilter<itk::Image<float,3>,itk::Image<float,3>  >    ImagePyramidType;
	typedef itk::Image<float,3>::RegionType      FixedImageRegionType;

	itk::Image< float , 3 >::Pointer pOutImage;
	//itk::Image< float , 3 >::Pointer  StartCorrelation(itk::Image<float,3>::Pointer
	typedef itk::Rigid3DTransform<double> Rigid3DTransformType;

 	igstkStandardClassBasicTraitsMacro(misMultiResCorrelation,misOldObject);
	igstkNewMacro(Self);

	itk::Rigid3DTransform<double>::Pointer  StartCorrelation(/*itk::Image<float,3>::Pointer
		pFixedImage ,itk::Image<float,3>::Pointer pMovingImage*/);

	typedef MultiResolutionRegistration<float> AppType;
	AppType::Pointer m_App;
	void Initialize();

	void StopCorrelation();

	HANDLE GetApplicationHandle();

	itk::Rigid3DTransform<double>::Pointer GetCurrentTransformMatrix();
	unsigned int GetCurrentIteration();
	unsigned int GetTotalIteration();

	void InitializeTransformMatrix(vtkMatrix4x4 * pMatrix);
	void SetPreparedPyramids(ImagePyramidType* FixedPyramid , ImagePyramidType* MovingPyramid);
	void SetFixedImageRegionPyramid(  std::vector<FixedImageRegionType> FixedRegion);

	void SetPermuteOrder(itk::FixedArray<unsigned int , 3> permute);
	void SetFlipAxes(itk::FixedArray<bool , 3> flip);
	void SetNumberOfLevel(int numberOfLevel);
	void ResetTotalIteration();
	void SetLevelInformation(vector<levelInformation> levelInfo);
	void SetTranslationScale(double transScale);

	 

	 bool IsRegistrationFinished();

private:
	unsigned int m_TotalIteration;
	HANDLE m_Application_Handle;
	bool m_Started = false;
  
};
#endif