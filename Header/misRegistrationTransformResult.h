#pragma once

struct misRegistrationTransformResult
{
public:
	vtkTransform* m_LandmarkRegistrationTransform;
	//vtkTransform* m_LandmarkRegistrationRefTransform;

	vtkTransform* m_SurfaceRegistrationTransform;
	//vtkTransform* m_SurfaceRegistrationRefTransform;

};