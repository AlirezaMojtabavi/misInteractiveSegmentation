#pragma once

#include "misVertebraEnum.h"
#include <vtkLineRepresentation.h>

class vtkActor;
class vtkPolyDataMapper;
class vtkLineSource;
class vtkSphereSource;
class vtkProperty;
class vtkPolyData;
class vtkPolyDataAlgorithm;
class vtkPointHandleRepresentation3D;
class vtkBox;
class vtkFollower;
class vtkVectorText;
class vtkPolyDataMapper;
class vtkCellPicker;

namespace parcast
{
	class I3DPlanCrossSectionFunction;
}
class IPlanWidgetRepresentation :
	public vtkWidgetRepresentation
{
public:
	
	enum InteractionPos { Outside = 0, OnP1, OnP2, TranslatingP1, TranslatingP2, OnLine, Scaling };
	vtkSetClampMacro(InteractionState, int, Outside, Scaling);
	// Get the three handle representations used for the vtkLineWidget2. 
	vtkGetObjectMacro(Point1Representation, vtkPointHandleRepresentation3D);
	vtkGetObjectMacro(Point2Representation, vtkPointHandleRepresentation3D);
	vtkGetObjectMacro(LineHandleRepresentation, vtkPointHandleRepresentation3D);


	virtual void SetScrewDiameter(double diameter) = 0;
	virtual void SetInteractionType(ScrewWidgetInteractionType type) = 0;
	virtual void SetMaxAllowedLineLen(double len) = 0;
	virtual void SetPointsWorldPosition(double x1[3], double x2[3]) = 0;
	virtual double* GetPoint1WorldPosition() = 0;
	virtual double* GetPoint2WorldPosition() = 0;
	virtual ScrewWidgetInteractionType GetInteractionType() = 0;
	virtual void SetLineColor(double r, double g, double b) = 0;
	virtual void SetScrewPlacementIsFinalized(bool finalized) = 0;
	virtual void HighlightLine(bool highlight) = 0;
protected :
	vtkPointHandleRepresentation3D *LineHandleRepresentation;
	vtkPointHandleRepresentation3D *Point1Representation;
	vtkPointHandleRepresentation3D *Point2Representation;
};

