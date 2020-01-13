#include "StdAfx.h"
#include "misPlaneWidget.h"
#include "vtkPlaneWidget.h"



misPlaneWidget::misPlaneWidget(void)
{
}


misPlaneWidget::~misPlaneWidget(void)
{
}

misPlaneWidget* misPlaneWidget::New()
{
	return  new misPlaneWidget;

}
void misPlaneWidget::PlaceWidget(double bds[6])
{
	int i;
	double bounds[6], center[3];

	this->AdjustBounds(bds, bounds, center);


	if ( this->NormalToYAxis )
	{
		this->PlaneSource->SetOrigin(bounds[0],center[1],bounds[4]);
		this->PlaneSource->SetPoint1(bounds[1],center[1],bounds[4]);
		this->PlaneSource->SetPoint2(bounds[0],center[1],bounds[5]);
	}
	else if ( this->NormalToZAxis )
	{
		this->PlaneSource->SetOrigin(bounds[0],bounds[2],center[2]);
		this->PlaneSource->SetPoint1(bounds[1],bounds[2],center[2]);
		this->PlaneSource->SetPoint2(bounds[0],bounds[3],center[2]);
	}
	else //default or x-normal
	{
		this->PlaneSource->SetOrigin(center[0],bounds[2],bounds[4]);
		this->PlaneSource->SetPoint1(center[0],bounds[3],bounds[4]);
		this->PlaneSource->SetPoint2(center[0],bounds[2],bounds[5]);
	}


	this->PlaneSource->Update();

	// Position the handles at the end of the planes
	this->PositionHandles();

	for (i=0; i<6; i++)
	{
		this->InitialBounds[i] = bounds[i];
	}

 
		this->InitialLength = sqrt((bounds[1]-bounds[0])*(bounds[1]-bounds[0]) +
			(bounds[3]-bounds[2])*(bounds[3]-bounds[2]) +
			(bounds[5]-bounds[4])*(bounds[5]-bounds[4]));

	// Set the radius on the sphere handles
	this->SizeHandles();
}
