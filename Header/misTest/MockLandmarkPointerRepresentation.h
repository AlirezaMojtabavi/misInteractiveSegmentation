
#pragma once

#include "ILandmarkPointerRepresentation.h"

MOCK_BASE_CLASS(MockLandmarkPointerRepresentation, ILandmarkPointerRepresentation)
{
	MOCK_CONST_METHOD(IsValid, 0, bool());
	MOCK_NON_CONST_METHOD(UpdateNormal, 0, void());
	MOCK_NON_CONST_METHOD(UpdateAsSelected, 0, void());
	MOCK_NON_CONST_METHOD(UpdateAsUnderCapture, 0, void());
	MOCK_NON_CONST_METHOD(Validate, 0, void());
	MOCK_NON_CONST_METHOD(InValidate, 0, void());
	MOCK_NON_CONST_METHOD(GetLandMark, 0, std::shared_ptr<misSpherePointLandmark>());
	MOCK_NON_CONST_METHOD(GetLablel, 0, std::shared_ptr<misSurfaceRepresentation>());
	MOCK_NON_CONST_METHOD(SetLabelPosition, 1, void(const double position[3]), SetLabelPosition1);
	MOCK_NON_CONST_METHOD(SetLabelPosition, 3, void(double x, double y, double z), SetLabelPosition2);
	MOCK_NON_CONST_METHOD(HideLandmarkLable, 0, void());
	MOCK_CONST_METHOD(GetCategory, 0, misLandmarkType());
	MOCK_NON_CONST_METHOD(GetAlllRepresentations, 0, std::vector<misSurfaceRepresentation>());
	MOCK_NON_CONST_METHOD(UpdateData, 1, void(LANDMARKLABELSTAUS landmarkStatus));
	MOCK_NON_CONST_METHOD(SetCorrectionVectorForLandmarkRegistration, 2, void(double mainPosition[3], double finalRegisteredPosition[3]));
	MOCK_NON_CONST_METHOD(GetPosition, 1, void(double position[3]));
	MOCK_CONST_METHOD(GetSurface, 0, std::shared_ptr<IRepresentation>());
	MOCK_NON_CONST_METHOD(SetVisibilityOn, 0, void());
	MOCK_NON_CONST_METHOD(SetVisibilityOff, 0, void());
	MOCK_NON_CONST_METHOD(SetCategory, 1, void(misLandmarkType val));
	MOCK_NON_CONST_METHOD(SetPosition, 1, void(const double position[3]), SetPosition1);
	MOCK_NON_CONST_METHOD(SetPosition, 3, void(double x, double y, double z), SetPosition2);
	MOCK_NON_CONST_METHOD(SetVisibility, 1, void(bool value));
	MOCK_NON_CONST_METHOD(SetColor, 4, void(float r, float g, float  b, float a));
	MOCK_NON_CONST_METHOD(SetLabelData, 3, void(int id, LANDMARKLABELSTAUS stat, LANDMARKLABLETYPE));
};
