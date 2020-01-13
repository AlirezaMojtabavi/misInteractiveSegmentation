#include "stdafx.h"
#include "MedicalCameraDirectionFactory.h"
#include "MedicalCameraDirectionSpine.h"
#include "MedicalCameraDirection.h"

 

std::shared_ptr <parcast::IMedicalCameraDirection> parcast::MedicalCameraDirectionFactory::Create(std::shared_ptr<I3DViewer> _3DViewer, misApplicationType type)
{
	std::shared_ptr <parcast::IMedicalCameraDirection> medicalCameraDirection;
	switch (type)
	{
	case misApplicationType::Spine:
		medicalCameraDirection = std::make_shared<parcast::MedicalCameraDirectionSpine>(_3DViewer);
		break;
	default:
		medicalCameraDirection = std::make_shared<parcast::MedicalCameraDirection>(_3DViewer);
		break;


	}
	return medicalCameraDirection;
}