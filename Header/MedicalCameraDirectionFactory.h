#pragma once
#include "IMedicalCameraDirection.h"
#include "misEnums.h"
#include "I3DViewer.h"

namespace parcast
{
	class MedicalCameraDirectionFactory
	{
	public:
		static std::shared_ptr <IMedicalCameraDirection> Create(std::shared_ptr<I3DViewer> _3DViewer, misApplicationType type);

	};
}