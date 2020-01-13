#pragma once
#include "IRepresentation.h"

namespace parcast
{
	class IMedicalCameraDirection
	{
	public:
		virtual ~IMedicalCameraDirection() = default;


		// Sets the camera focal point to the default value and the camera view up along the y axis. Then it places the camera right 
		// _above_ the focal point by a distance proportional to height of GetBounds() and GetScaleCameraPosition().
		virtual void SetSupriorView() = 0;

		// Sets the camera focal point to the default value and the camera view up along the y axis. Then it places the camera right 
		// _above_ the focal point by a distance proportional to height of GetBounds() and GetScaleCameraPosition().
		virtual void SetInferiorView() = 0;

		// Sets the camera focal point to the default value and the camera view up along negative z axis. Then it places the camera 
		// next to the focal point by a displacement along the Y direction proportional to width of bounding box and 
		// GetScaleCameraPosition().
		virtual void SetAnteriorView() = 0;

		// Sets the camera focal point to the default value and the camera view up along negative z axis. Then it places the camera 
		// next to the focal point by a displacement along the negative Y axis proportional to width (Y) of bounding box and 
		// GetScaleCameraPosition().
		virtual void SetPosteriorView() = 0;

		// Sets the camera focal point to the default value and the camera view up along negative z axis. Then it places the camera 
		// next to the focal point by a displacement along the X axis proportional to width (Y) of bounding box and 
		// GetScaleCameraPosition().
		virtual void SetLeftView() = 0;

		// Sets the camera focal point to the default value and the camera view up along negative z axis. Then it places the camera 
		// next to the focal point by a displacement along the negative X axis proportional to width (Y) of bounding box and 
		// GetScaleCameraPosition().
		virtual void SetRightView() = 0;

		virtual void SetMainRepresentation(std::shared_ptr<IRepresentation> val) = 0;
		virtual void SetDefaultVeiw() = 0;
	};
}
