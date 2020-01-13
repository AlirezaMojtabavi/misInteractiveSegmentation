#pragma once
#include <misEnums.h>
#include <IImage.h>

class ICorrelationUpdateTransform
{
public:
	virtual ~ICorrelationUpdateTransform() = default;
 	virtual	void UpdateTransform(std::shared_ptr<IImage> m_FixedImage,
		std::shared_ptr<IImage> m_MovingImage,
		misRegistrationMode m_RegistrationMode,
		bool& m_TransformMatrixModification) = 0;

};
