#pragma once

#include "IToolRepresentation.h"

MOCK_BASE_CLASS(MockToolRepresentation, IToolRepresentation)
{
	MOCK_NON_CONST_METHOD(SetToolRepresentationType, 1, void(misToolRepresentationType  ));
	MOCK_NON_CONST_METHOD(SetTorusRadious, 1, void(double radious));
	MOCK_NON_CONST_METHOD(SetTorusVisibility, 1, void(bool value));
	MOCK_NON_CONST_METHOD(SetVirtualTipVisibility, 1, void(bool value));
	MOCK_NON_CONST_METHOD(SetVirtualTipLength, 1, void(double length));
	MOCK_NON_CONST_METHOD(SetColor, 3, void(float r, float g, float  b));
	MOCK_NON_CONST_METHOD(SetVisibilityOn, 0, void(void));
	MOCK_NON_CONST_METHOD(SetVisibilityOff, 0, void(void));
	MOCK_NON_CONST_METHOD(SetVisibility, 1, void(bool));
	MOCK_NON_CONST_METHOD(GetToolProperties, 0, misToolProperties(void));
	MOCK_NON_CONST_METHOD(SetPolyData, 3, vtkActor*(vtkAlgorithmOutput* polyData, misToolProperties toolProperties,
		misToolRepresentationType currentToolRepTypemisToolProperties));
	MOCK_NON_CONST_METHOD(SetMeasurementVirtualTip, 1, void(bool ));
	MOCK_NON_CONST_METHOD(SetUserTransform, 1, void(vtkTransform *transform) );
	MOCK_CONST_METHOD(GetSurface, 0, std::shared_ptr<IRepresentation> () );
};
