#pragma once

#include "misLandmarkBasedRegistrationCalculator.h"
#include "misImageGeoProperties.h"

class  misImageToImageLandmarkBasedRegistration : public misLandmarkBasedRegistrationCalculator
{
public:
	misImageToImageLandmarkBasedRegistration(int minimumPointForRegistration, int initialNumberOfPointsForRegistration,
		misLandmarkBasedRegistrationCalculationType landmarkType);
	std::vector<mislandMarkPosAndStatusStr> GetConvertedMovableLandmarkList();
	std::vector<mislandMarkPosAndStatusStr> GetRegisteredMovableLandmarkDataList();
	void SetFixedProperty(misImageGeoProperties FixedImageProps);
	void SetMovingProperty(misImageGeoProperties MovingImageProps);
	// important NOTE : this  land mark is captured from transformed plane
	void AddTransformedMovableLandmark(int index, double capturedPosition[3]);
	vtkTransform* getFinalTransform();
	void SetInitialMatrix(vtkMatrix4x4* correlationRes);
	void ResetInitialMatrix(void);
	bool IsNumberOfRegisterdPointsEnough();
private:
	vtkTransform* CalculateMovingTransform(double * MovingScalingFactor);
	vtkTransform* CalculateFixedTransform(double * FixedScalingFactor);
	vtkTransform* CalculateInverseMovingTransform(double * MovingScalingFactor);
	double* CalculateFixedFactor();
	double* CalculateMovingFactor();
	double* ApplyInversTransformMatrixOnNewLandmark(double capturedPosition[3]);
	void CalculateTextureGeoTransform();

private:
	misImageGeoProperties m_FixedImageProps;
	misImageGeoProperties m_MovingImageProps;
	vtkTransform* m_FinalRegistrationTransform;
	vtkTransform* m_LandmarkTransform;
};