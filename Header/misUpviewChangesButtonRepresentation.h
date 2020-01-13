#pragma once

#include "vtkBorderRepresentation.h"

class vtkRenderer;
class vtkRenderWindowInteractor;
class vtkCamera;
class vtkCameraInterpolator;
class vtkPoints;
class vtkPolyData;
class vtkTransformPolyDataFilter;
class vtkPolyDataMapper2D;
class vtkProperty2D;
class vtkActor2D;

class misUpviewChangesButtonRepresentation: public vtkBorderRepresentation
{
public:
	// Description:
	// Instantiate this class.
	static misUpviewChangesButtonRepresentation *New();

	// Description:
	// Specify the camera to interpolate. This must be specified by
	// the user.
	void SetCamera(vtkCamera *camera);
	vtkGetObjectMacro(Camera,vtkCamera);

	// Description:
	// By obtaining this property you can specify the properties of the 
	// representation.
	vtkGetObjectMacro(Property,vtkProperty2D);

	void TurnCameraToTheLeft();
	void TurnCameraToTheRight();
	void InitializePath();

	// Description:
	// Satisfy the super classes' API.
	virtual void BuildRepresentation();

	int		RenderOverlay(vtkViewport *w);
	int		RenderOpaqueGeometry(vtkViewport *w);
	int		RenderTranslucentPolygonalGeometry(vtkViewport *w);
	void	SetRatioChangesOfViewUp( double ratioChange );


protected:
	misUpviewChangesButtonRepresentation();
	~misUpviewChangesButtonRepresentation();

	vtkCamera					*Camera;
	vtkPoints					*Points;
	vtkPolyData					*PolyData;
	vtkTransformPolyDataFilter	*TransformFilter;
	vtkPolyDataMapper2D			*Mapper;
	vtkProperty2D				*Property;
	vtkActor2D					*Actor;

private:
	misUpviewChangesButtonRepresentation(const misUpviewChangesButtonRepresentation&);  //Not implemented
	void operator=(const misUpviewChangesButtonRepresentation&);  //Not implemented
	//double m_ViewUp[3];
	double m_RatioChangesOfViewUp;
};

