#pragma once
#include "IValidLandmarksEnumerator.h"
#include "IImageToPatientLandmarkBasedRegistation.h"

class misValidLandmarksEnumerator :
	public IValidLandmarksEnumerator
{
public:
	misValidLandmarksEnumerator(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> landmark);
	size_t GetNumberofCurrentValidLandmarks() override;
private:
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_pLandmarkList;
};

