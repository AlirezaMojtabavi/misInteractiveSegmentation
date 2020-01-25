#pragma once

#include "misLandmarkenums.h"
#include "IPackagePlanRel.h"
#include "IOblqueView.h"

class ISimpleDataPackage;
class misCompeletePlanDataDependensiesStrct;

namespace parcast
{

	class IPlanningGroupViewer: public IOblqueView
	{
	public:
		virtual ~IPlanningGroupViewer() = default;

		virtual void ReleaseResource() = 0;
		virtual void SetExternalEventViewer(std::function<void(itk::Object *caller, const itk::EventObject& pEvent)> val) = 0;
	
		virtual void ShowPackage(std::shared_ptr<ISimpleDataPackage> pPackage, bool resetZoom ) = 0;
		virtual void SetTransformMatrix(vtkMatrix4x4* transform) = 0;
		virtual void SetObliqueFlag(bool isObique) = 0;
		virtual void UpdatePanoramicCurve() = 0;
		virtual void RefreshCurrentPackage() = 0;
		virtual void SetPlanCentricViewAngle(double angle) = 0;
	};

}