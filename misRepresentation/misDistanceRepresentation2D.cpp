#include "stdafx.h"
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: misDistanceRepresentation2D.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "misDistanceRepresentation2D.h"

using namespace std;
 
 
vtkStandardNewMacro(misDistanceRepresentation2D);
//----------------------------------------------------------------------
misDistanceRepresentation2D::misDistanceRepresentation2D()
{

	this->IsNormalWidget = true;
	this->m_Orientation = UNKnownDirection;
}

//----------------------------------------------------------------------
misDistanceRepresentation2D::~misDistanceRepresentation2D()
{
 
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::GetPoint1WorldPosition(double pos[3])
{
  this->Point1Representation->GetWorldPosition(pos);
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::GetPoint2WorldPosition(double pos[3])
{
  this->Point2Representation->GetWorldPosition(pos);
}

//----------------------------------------------------------------------
double* misDistanceRepresentation2D::GetPoint1WorldPosition()
{
  if (!this->Point1Representation)
    {
    static double temp[3]=  {0, 0, 0};
    return temp;
    }
  return this->Point1Representation->GetWorldPosition();
}

//----------------------------------------------------------------------
double* misDistanceRepresentation2D::GetPoint2WorldPosition()
{
  if (!this->Point2Representation)
    {
    static double temp[3]=  {0, 0, 0};
    return temp;
    }
  return this->Point2Representation->GetWorldPosition();
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::SetPoint1DisplayPosition(double x[3])
{
  this->Point1Representation->SetDisplayPosition(x);
  double p[3];
  this->Point1Representation->GetWorldPosition(p);
  this->Point1Representation->SetWorldPosition(p);
  this->AxisActor->GetPoint1Coordinate()->SetValue(p);
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::SetPoint2DisplayPosition(double x[3])
{
  this->Point2Representation->SetDisplayPosition(x);
  double p[3];
  this->Point2Representation->GetWorldPosition(p);
  this->Point2Representation->SetWorldPosition(p);
  this->AxisActor->GetPoint2Coordinate()->SetValue(p);
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::SetPoint1WorldPosition(double x[3])
{
  if (this->Point1Representation)
    {
    this->Point1Representation->SetWorldPosition(x);
    this->AxisActor->GetPoint1Coordinate()->SetValue(x);
    }
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::SetPoint2WorldPosition(double x[3])
{
  if (this->Point2Representation)
    {
    this->Point2Representation->SetWorldPosition(x);
    this->AxisActor->GetPoint2Coordinate()->SetValue(x);
    }
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::GetPoint1DisplayPosition(double pos[3])
{
  this->Point1Representation->GetDisplayPosition(pos);
  pos[2] = 0.0;
}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::GetPoint2DisplayPosition(double pos[3])
{
  this->Point2Representation->GetDisplayPosition(pos);
  pos[2] = 0.0;
}

//----------------------------------------------------------------------
//vtkAxisActor2D *misDistanceRepresentation2D::GetAxis()
//{
//  return this->AxisActor;
//}

//----------------------------------------------------------------------
void misDistanceRepresentation2D::BuildRepresentation()
{
	string measurmentFactor;
  if ( this->GetMTime() > this->BuildTime ||
       this->Point1Representation->GetMTime() > this->BuildTime ||
       this->Point2Representation->GetMTime() > this->BuildTime ||
       (this->Renderer && this->Renderer->GetVTKWindow() &&
        this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime) )
    {
    this->Superclass::BuildRepresentation();
	//vtkDistanceRepresentation::BuildRepresentation();
    // Okay, compute the distance and set the label
    double p1[3], p2[3];
    this->Point1Representation->GetWorldPosition(p1);
    this->Point2Representation->GetWorldPosition(p2);

	switch (this->GetImageOrientation())
	{
	case  AXIAL :
			  p2[2] = p1[2];
		break;
	case  SAGITTAL:
			  p2[0] = p1[0];
		break;
	case CORONAL:
			 p2[1] = p1[1];
		break;
	}

    this->Distance = sqrt(vtkMath::Distance2BetweenPoints(p1,p2));
    char t_string[512];
    sprintf_s(t_string, this->LabelFormat, this->Distance);
	measurmentFactor.append(t_string);
	measurmentFactor.append("mm");
	this->AxisActor->SetTitle(measurmentFactor.c_str());

    this->BuildTime.Modified();
    }
  
}

void misDistanceRepresentation2D::SetPoint1ToFocalPoint( double *pos )
{
	double position[3];
	position[0] = pos[0]; 
	position[1] = pos[1];
	position[2] = pos[2];
	this->SetPoint1DisplayPosition(position);
	
}

void misDistanceRepresentation2D::StartWidgetInteraction( double e[2] )
{
	
	double pos[3];
	pos[0] = e[0];
	pos[1] = e[1];
	pos[2] = 0.0;
	if (this->IsNormalWidget)
		this->SetPoint1DisplayPosition(pos);
	this->SetPoint2DisplayPosition(pos);
}

void misDistanceRepresentation2D::setRepresentationMode( bool type )
{
	if (!type)
		this->IsNormalWidget = false;
}

void misDistanceRepresentation2D::SetImageOrientation( IMAGEORIENTATION orientation )
{
	this->m_Orientation = orientation;
}

IMAGEORIENTATION misDistanceRepresentation2D::GetImageOrientation()
{
	return this->m_Orientation;
}

//
//void misDistanceRepresentation2D::WidgetInteraction( double e[2] )
//{
//	double pos[3];
//	pos[0] = e[0];
//	pos[1] = e[1];
//	pos[2] = 0.0;
//	this->SetPoint2DisplayPosition(pos);
//}


//----------------------------------------------------------------------
//void misDistanceRepresentation2D::ReleaseGraphicsResources(vtkWindow *w)
//{
//  this->AxisActor->ReleaseGraphicsResources(w);
//}
//
////----------------------------------------------------------------------
//int misDistanceRepresentation2D::RenderOverlay(vtkViewport *v)
//{
//  this->BuildRepresentation();
//
//  if ( this->AxisActor->GetVisibility() )
//    {
//    return this->AxisActor->RenderOverlay(v);
//    }
//  else
//    {
//    return 0;
//    }
//}
//
////----------------------------------------------------------------------
//int misDistanceRepresentation2D::RenderOpaqueGeometry(vtkViewport *v)
//{
//  this->BuildRepresentation();
//
//  if ( this->AxisActor->GetVisibility() )
//    {
//    return this->AxisActor->RenderOpaqueGeometry(v);
//    }
//  else
//    {
//    return 0;
//    }
//}
//
////----------------------------------------------------------------------
//void misDistanceRepresentation2D::PrintSelf(ostream& os, vtkIndent indent)
//{
//  //Superclass typedef defined in vtkTypeMacro() found in vtkSetGet.h
//  this->Superclass::PrintSelf(os,indent);
//}
