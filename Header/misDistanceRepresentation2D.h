/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: misDistanceRepresentation2D.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME misDistanceRepresentation2D - represent the vtkDistanceWidget
// .SECTION Description
// The misDistanceRepresentation2D is a representation for the
// vtkDistanceWidget. This representation consists of a measuring line (axis)
// and two vtkHandleWidgets to place the end points of the line. Note that
// this particular widget draws its representation in the overlay plane.

// .SECTION See Also
// vtkDistanceWidget vtkDistanceRepresentation


#ifndef __misDistanceRepresentation2D_h
#define __misDistanceRepresentation2D_h

#include "VisualizationGeneralTypes.h"

class vtkAxisActor2D;
class vtkProperty2D;


class misDistanceRepresentation2D : public vtkDistanceRepresentation2D
{
public:
  // Description:
  // Instantiate class.
  static misDistanceRepresentation2D *New();

 
 // void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Satisfy the superclasses API.
  //virtual double GetDistance()
  //  {return this->Distance;}

  // Description:
  // Methods to Set/Get the coordinates of the two points defining
  // this representation. Note that methods are available for both
  // display and world coordinates.
  double* GetPoint1WorldPosition();
  double* GetPoint2WorldPosition();
  void GetPoint1WorldPosition(double pos[3]);
  void GetPoint2WorldPosition(double pos[3]);
  void SetPoint1WorldPosition(double pos[3]);
  void SetPoint2WorldPosition(double pos[3]);

  void SetPoint1DisplayPosition(double pos[3]);
  void SetPoint2DisplayPosition(double pos[3]);
  void GetPoint1DisplayPosition(double pos[3]);
  void GetPoint2DisplayPosition(double pos[3]);

  // Description:
  // Retrieve the vtkAxisActor2D used to draw the measurement axis. With this
  // properties can be set and so on.
  //vtkAxisActor2D *GetAxis();

  // Description:
  // Method to satisfy superclasses' API.
  virtual void BuildRepresentation();
  void SetPoint1ToFocalPoint(double *pos);
  void StartWidgetInteraction(double e[2]);
 // void WidgetInteraction(double e[2]);
  void setRepresentationMode(bool type);
  void SetImageOrientation(IMAGEORIENTATION);
  IMAGEORIENTATION GetImageOrientation();

  // Description:
  // Methods required by vtkProp superclass.
  /*virtual void ReleaseGraphicsResources(vtkWindow *w);
  virtual int RenderOverlay(vtkViewport *viewport);
  virtual int RenderOpaqueGeometry(vtkViewport *viewport);*/

protected:
  misDistanceRepresentation2D();
  ~misDistanceRepresentation2D();
  bool IsNormalWidget;
  IMAGEORIENTATION m_Orientation;
  

  // Add a line to the mix
  /*vtkAxisActor2D *AxisActor;
  vtkProperty2D  *AxisProperty;*/

  // The distance between the two points
  //double Distance;

private:
  misDistanceRepresentation2D(const misDistanceRepresentation2D&);  //Not implemented
  void operator=(const misDistanceRepresentation2D&);  //Not implemented
};

#endif
