#include "..\Header\misFollowerFixedArea.h"
#include "..\Header\misFollowerFixedArea.h"
#include "..\Header\misFollowerFixedArea.h"
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: misFollowerFixedArea.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

	 This software is distributed WITHOUT ANY WARRANTY; without even
	 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	 PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "stdafx.h"
#include "misFollowerFixedArea.h"



#include <math.h>
vtkStandardNewMacro(misFollowerFixedArea);

vtkCxxSetObjectMacro(misFollowerFixedArea, Camera, vtkCamera);

// Creates a follower with no camera set
misFollowerFixedArea::misFollowerFixedArea()
	
{
	Camera = NULL;
	Device = vtkActor::New();
	m_ScaleCoef = 9500;

	m_ClampScaleRange[0] = 1;;
	m_ClampScaleRange[1] = 1.5;
	PickableOn();
	DragableOn();
}

misFollowerFixedArea::~misFollowerFixedArea()
{
	if (Camera)
	{
		Camera->UnRegister(this);
	}

	Device->Delete();
}

// Copy the follower's composite 4x4 matrix into the matrix provided.
void misFollowerFixedArea::GetMatrix(vtkMatrix4x4 *result)
{
	Transform->Push();
	Transform->PostMultiply();
	Transform->Identity();
	this->GetOrientation();

	Transform->Translate(-Origin[0],
		-Origin[1],
		-Origin[2]);
	Transform->Scale(Scale[0],
		Scale[1],
		Scale[2]);
	Transform->RotateY(Orientation[1]);
	Transform->RotateX(Orientation[0]);
	Transform->RotateZ(Orientation[2]);
	if (Camera)
	{
		auto pos = Camera->GetPosition();
		auto vup = Camera->GetViewUp();
		double Rx[3], Ry[3], Rz[3];
		if (Camera->GetParallelProjection())
		{
			Camera->GetDirectionOfProjection(Rz);
			Rz[0] = -Rz[0];
			Rz[1] = -Rz[1];
			Rz[2] = -Rz[2];
		}
		else
		{
			auto distance = sqrt(
				(pos[0] - Position[0])*(pos[0] - Position[0]) +
				(pos[1] - Position[1])*(pos[1] - Position[1]) +
				(pos[2] - Position[2])*(pos[2] - Position[2]));
			for (int i = 0; i < 3; i++)
			{
				Rz[i] = (pos[i] - Position[i]) / distance;
			}
		}

		double dop[3], vur[3];
		Camera->GetDirectionOfProjection(dop);
		vtkMath::Cross(dop, vup, vur);
		vtkMath::Normalize(vur);
		vtkMath::Cross(Rz, vur, Ry);
		vtkMath::Normalize(Ry);
		vtkMath::Cross(Ry, Rz, Rx);
		auto  matrix = vtkSmartPointer<vtkMatrix4x4>::New();
		matrix->Element[0][0] = Rx[0];
		matrix->Element[1][0] = Rx[1];
		matrix->Element[2][0] = Rx[2];
		matrix->Element[0][1] = Ry[0];
		matrix->Element[1][1] = Ry[1];
		matrix->Element[2][1] = Ry[2];
		matrix->Element[0][2] = Rz[0];
		matrix->Element[1][2] = Rz[1];
		matrix->Element[2][2] = Rz[2];
		Transform->Concatenate(matrix);
	}

	double p1[3];
	p1[0] = Origin[0] + Position[0];
	p1[1] = Origin[1] + Position[1];
	p1[2] = Origin[2] + Position[2];
	float lenght = DistanceToCamera();
	float m_3DZoomScaleFactor = sqrt(lenght) / sqrt(m_ScaleCoef + m_distance2Plane* m_ScaleCoef);
	if (m_3DZoomScaleFactor > m_ClampScaleRange[1])
	{
		m_3DZoomScaleFactor = m_ClampScaleRange[1];
	}
	if (m_3DZoomScaleFactor < m_ClampScaleRange[0])
	{
		m_3DZoomScaleFactor = m_ClampScaleRange[0];
	}
	
	bool parallell = false;
	float parallellScale = 1;
	if (m_Renderer)
	{
		parallell = m_Renderer->GetActiveCamera()->GetParallelProjection();
		parallellScale = m_Renderer->GetActiveCamera()->GetParallelScale();
	}
	if (parallell)
	{
		Transform->Scale((parallellScale / 100.0)*m_3DZoomScaleFactor, (parallellScale / 100.0)*m_3DZoomScaleFactor, (parallellScale / 100.0)*m_3DZoomScaleFactor);
	}
	else
		Transform->Scale(m_3DZoomScaleFactor, m_3DZoomScaleFactor, m_3DZoomScaleFactor);
	Transform->Translate(p1[0], p1[1], p1[2]);	
	if (UserMatrix)
	{
		Transform->Concatenate(UserMatrix);
	}
	
	if (!m_DisableDepth)
	{
		auto transformCamera = ComputeShiftTransform(Camera, m_distance2Plane);
		Transform->Concatenate(transformCamera);
	}
		
	Transform->GetMatrix(result);

}




void misFollowerFixedArea::Render(vtkRenderer *ren)
{
	m_Renderer = ren;
	Property->Render(this, ren);

	vtkMatrix4x4 *matrix = vtkMatrix4x4::New();

	Device->SetProperty(Property);
	Property->Render(this, ren);
	if (BackfaceProperty)
	{
		BackfaceProperty->BackfaceRender(this, ren);
		Device->SetBackfaceProperty(BackfaceProperty);
	}

	/* render the texture */
	if (Texture)
	{
		Texture->Render(ren);
	}

	// make sure the device has the same matrix
	GetMatrix(matrix);
	Device->SetUserMatrix(matrix);
	//Build_Transformation(ren);
	Device->Render(ren, Mapper);
	//Pop_Transformation_Matrix();
	matrix->Delete();
}

void misFollowerFixedArea::GetMatrix(double m[16])
{
	GetMatrix(Matrix);
	vtkMatrix4x4::DeepCopy(m, Matrix);
}



float misFollowerFixedArea::DistanceToCamera()
{
	float lenght = 0;
	if (m_Renderer)
	{
		vtkCamera* pCam = m_Renderer->GetActiveCamera();
		double* positionCam = pCam->GetPosition();
		double width[3];
		double pos[3];
		GetPosition(pos);
		for (int i = 0; i < 3; i++)
			width[i] = pos[i] - positionCam[i];
		lenght = vtkMath::Dot(width, width);

	}	return lenght;
}

 vtkSmartPointer<vtkTransform> misFollowerFixedArea::ComputeShiftTransform(vtkCamera* camera, double distance2Plane)
{
	double position[3];
	camera->GetPosition(position);
	double focalPoint[3];
	camera->GetFocalPoint(focalPoint);
	double cameraDirection[3];
	for (int i = 0; i < 3; i++)
		cameraDirection[i] = position[i] - focalPoint[i];
	vtkMath::Normalize(cameraDirection);
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->PostMultiply();
	for (int i = 0; i < 3; i++)
		cameraDirection[i] = cameraDirection[i] * distance2Plane;
	transform->Translate(cameraDirection[0], cameraDirection[1], cameraDirection[2]);
	return transform;
}

 int misFollowerFixedArea::RenderOpaqueGeometry(vtkViewport *vp)
 {
	 if (!this->Mapper)
	 {
		 return 0;
	 }

	 if (!this->Property)
	 {
		 // force creation of a property
		 this->GetProperty();
	 }

	 if (this->GetIsOpaque())
	 {
		 vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
		 this->Render(ren);
		 return 1;
	 }
	 return 0;
 }

 //-----------------------------------------------------------------------------
 int misFollowerFixedArea::RenderTranslucentPolygonalGeometry(vtkViewport *vp)
 {
	 if (!this->Mapper)
	 {
		 return 0;
	 }

	 if (!this->Property)
	 {
		 // force creation of a property
		 this->GetProperty();
	 }

	 if (!this->GetIsOpaque())
	 {
		 vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
		 this->Render(ren);
		 return 1;
	 }
	 return 0;
 }

 //-----------------------------------------------------------------------------
 // Description:
 // Does this prop have some translucent polygonal geometry?
 int misFollowerFixedArea::HasTranslucentPolygonalGeometry()
 {
	 if (!this->Mapper)
	 {
		 return 0;
	 }
	 // make sure we have a property
	 if (!this->Property)
	 {
		 // force creation of a property
		 this->GetProperty();
	 }

	 // is this actor opaque ?
	 return !this->GetIsOpaque();
 }

 void misFollowerFixedArea::DisableDepthOn()
 {
	 m_DisableDepth = true;
 }

 void misFollowerFixedArea::DisableDepthOff()
 {
	 m_DisableDepth = false;
 }

 void misFollowerFixedArea::SetDisableDepth(bool state)
 {
	 m_DisableDepth = state;
 }
