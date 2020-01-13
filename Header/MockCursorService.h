#pragma once

#include "ICursorService.h"

MOCK_BASE_CLASS(MockCursorService, ICursorService)
{
	MOCK_NON_CONST_METHOD(SetWidgetInteractor, 1, void(vtkRenderWindowInteractor* pInteractor));
	MOCK_NON_CONST_METHOD(SetRenderer, 1, void(vtkRenderer* renderer));
	MOCK_NON_CONST_METHOD(SetImageOrientation, 1, void(IMAGEORIENTATION imgOrintation));
	MOCK_NON_CONST_METHOD(SetWidgetLineWeight, 1, void(double weight));
	MOCK_NON_CONST_METHOD(SetWidgetType, 1, void(misCursorType widgetType));
	MOCK_NON_CONST_METHOD(SetWidgetBounds, 1, void(double* pBounds));
	MOCK_NON_CONST_METHOD(ApplyWidget, 1, void(vtkProp3D* actor));
	MOCK_NON_CONST_METHOD(CreateWidget, 1, void(double));
	MOCK_NON_CONST_METHOD(EnableWidget, 0, void());
	MOCK_NON_CONST_METHOD(DisableWidget, 0, void());
	MOCK_NON_CONST_METHOD(ReleaseWidget, 0, void());
	MOCK_NON_CONST_METHOD(ChangeWidgetType, 1, void(misCursorType cursorType));
	MOCK_NON_CONST_METHOD(AddObserver, 1, void(vtkCommand* pWdgObserver));
	MOCK_NON_CONST_METHOD(Set3DInteractionCapturedFlag, 1, void(bool val));
	MOCK_NON_CONST_METHOD(UpdateWidgetPosition, 0, void());
	MOCK_NON_CONST_METHOD(SetCornerProperties, 1, void(std::shared_ptr<ICornerProperties> pCornerProperties));
	MOCK_NON_CONST_METHOD(SetAxesColors, 1, void(const parcast::AxesColors& colors));
};

