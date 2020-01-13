#pragma once
#include "misToolProperties.h"
#include "IRepresentation.h"

class IToolRepresentation
{
public:
	virtual ~IToolRepresentation() = default;
	virtual void SetToolRepresentationType(misToolRepresentationType  toolRepType) = 0;
	virtual void SetTorusVisibility(bool value) = 0;
	virtual void SetVirtualTipVisibility(bool value) = 0;
	virtual void SetVirtualTipLength(double length) = 0;
	virtual void SetColor(float r, float g, float  b) = 0;
	virtual void SetVisibilityOn(void) = 0;
	virtual void SetVisibilityOff(void) = 0;
	virtual void SetVisibility(bool m_Visibility) = 0;
	virtual misToolProperties GetToolProperties(void) = 0;
	virtual vtkSmartPointer<vtkActor> SetPolyData(vtkSmartPointer<vtkPolyData> polyData, misToolProperties toolProperties,
		misToolRepresentationType currentToolRepTypemisToolProperties) = 0;
	//Gets a vtkTransform and calls TransformDoublePoint(0,0,0) and then sets the result transform to all actors
	virtual void SetUserTransform(vtkTransform *transform) = 0;
	virtual std::shared_ptr<IRepresentation> GetSurface() const = 0;
 };

