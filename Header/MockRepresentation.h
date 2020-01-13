#pragma once

#include "IRepresentation.h"

MOCK_BASE_CLASS(MockRepresentation,IRepresentation)
{
	MOCK_NON_CONST_METHOD(AddObserver, 2, unsigned long(const itk::EventObject & event, itk::Command *));
	MOCK_NON_CONST_METHOD(InvokeEvent, 1, void(const itk::EventObject& event));
	MOCK_CONST_METHOD(HasObserver, 1, bool(const itk::EventObject & event));
	MOCK_CONST_METHOD(GetObjectName, 0, std::string());
	MOCK_NON_CONST_METHOD(SetObjectName, 1, void(std::string val));
	MOCK_NON_CONST_METHOD(SetRepresentationName, 1, void(std::string name));
	MOCK_NON_CONST_METHOD(AddProp, 1, void(vtkProp*));
	MOCK_NON_CONST_METHOD(SetVisibilityOff, 0, void(void));
	MOCK_NON_CONST_METHOD(SetVisibility, 1, void(bool value));
	MOCK_NON_CONST_METHOD(SetVisibilityOn, 0, void(void));
	MOCK_NON_CONST_METHOD(GetNumberOfActors, 0, int());
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(SetPosition, 1, void(double position[3]), identifier_1);
	MOCK_NON_CONST_METHOD(SetPosition, 3, void(double x, double y, double z), identifier_2);
	MOCK_CONST_METHOD(GetPosition, 0, double*(), identifier_3);
	MOCK_NON_CONST_METHOD(GetPosition, 1, void(double position[3]), identifier_4);
	MOCK_NON_CONST_METHOD(SetUserTransform, 1, void(vtkTransform *transform));
	MOCK_NON_CONST_METHOD(GetActor, 1, vtkProp*(int index));
	MOCK_NON_CONST_METHOD(CalculatedBoundingBox, 0, bool());
	typedef itk::BoundingBox<double, 3, double>::Pointer BoundingBoxType;
	MOCK_NON_CONST_METHOD(GetBoundingBox, 0, BoundingBoxType(), identifier_5);
	MOCK_NON_CONST_METHOD(GetBoundingBox, 1, bool(double *boundingBox), identifier_6);
	MOCK_CONST_METHOD(GetActors, 0, ActorsListType());
};
