#pragma once

#include "IPlanningGroupViewer.h"

#include "misCompeletePlanDataDependensiesStrct.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPlanningGroupViewer, IPlanningGroupViewer)
	{
		MOCK_NON_CONST_METHOD(ReleaseResource, 0, void());
		MOCK_NON_CONST_METHOD(SetExternalEventViewer, 1, void(std::function<void(itk::Object *, const itk::EventObject&)>));
		MOCK_NON_CONST_METHOD(VolumeLandmarkCaptureDisable, 0, void());
		MOCK_NON_CONST_METHOD(ImageLandmarkCaptureEnable, 3, void(misLandmarkType, int, LANDMARKLABLETYPE));
		MOCK_NON_CONST_METHOD(ImageLandmarkCaptureDisable, 0, void());
		MOCK_NON_CONST_METHOD(ShowPackage, 2, void(std::shared_ptr<ISimpleDataPackage>, bool));
		MOCK_NON_CONST_METHOD(SetTransformMatrix, 1, void(vtkMatrix4x4* transform));
		MOCK_NON_CONST_METHOD(SetObliqueFlag, 1, void(bool isObique));
		MOCK_NON_CONST_METHOD(UpdatePanoramicCurve, 0, void());
		MOCK_NON_CONST_METHOD(RefreshCurrentPackage, 0, void());
		MOCK_NON_CONST_METHOD(ShowPlan, 1, void(std::shared_ptr< parcast::IPackagePlanRel> rel));
		MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double));

	};

}
