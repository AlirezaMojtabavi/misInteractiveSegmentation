#include "StdAfx.h"
#include "misUpviewChangesButtonRepresentation.h"

vtkCxxRevisionMacro(misUpviewChangesButtonRepresentation, "$Revision: 1.5 $");
vtkStandardNewMacro(misUpviewChangesButtonRepresentation);

misUpviewChangesButtonRepresentation::misUpviewChangesButtonRepresentation(void)
{
	this->Camera = NULL;

	// Set up the 
	double size[2];
	this->GetSize(size);
	//this->Position2Coordinate->SetValue(0.75, 0.75);
	this->ProportionalResize = 1;
	this->Moving = 1;
	this->ShowBorder = vtkBorderRepresentation::BORDER_ON;

	// Create the geometry in canonical coordinates
	this->Points = vtkPoints::New();
	this->Points->SetDataTypeToDouble();
	this->Points->SetNumberOfPoints(6);

	//these 3 lines determine this:
	//		.
	//			.
	//		.
	this->Points->SetPoint(0, 0.55,  0.0, 0.0);
	this->Points->SetPoint(1, 1.0, 0.5, 0.0);
	this->Points->SetPoint(2, 0.55,  1.0, 0.0);

	//these 3 lines determine this:
	//			.
	//		.
	//			.
	this->Points->SetPoint(3, 0.0,  0.5, 0.0);
	this->Points->SetPoint(4, 0.45,  0.0, 0.0);
	this->Points->SetPoint(5, 0.45,  1.0, 0.0);
	/*this->Points->SetPoint(6, 1.0,  0.0, 0.0);*/
 


	vtkCellArray *cells = vtkCellArray::New();
	cells->InsertNextCell(3); //Right arrow
	cells->InsertCellPoint(0);
	cells->InsertCellPoint(1);
	cells->InsertCellPoint(2);

	cells->InsertNextCell(3); //Left arrow
	cells->InsertCellPoint(3);
	cells->InsertCellPoint(4);
	cells->InsertCellPoint(5);
	/*cells->InsertCellPoint(6);*/
	
	this->PolyData = vtkPolyData::New();
	this->PolyData->SetPoints(this->Points);
	this->PolyData->SetPolys(cells);
	cells->Delete();

	this->TransformFilter = vtkTransformPolyDataFilter::New();
	this->TransformFilter->SetTransform(this->BWTransform);
	this->TransformFilter->SetInput(this->PolyData);

	this->Mapper = vtkPolyDataMapper2D::New();
	this->Mapper->SetInput(this->TransformFilter->GetOutput());
	
	this->Property = vtkProperty2D::New();
	this->Actor = vtkActor2D::New();
	this->Actor->SetMapper(this->Mapper);
	this->Actor->SetProperty(this->Property);

	this->m_RatioChangesOfViewUp = 0.0;
}

misUpviewChangesButtonRepresentation::~misUpviewChangesButtonRepresentation()
{
	this->SetCamera(0);
	this->Points->Delete();
	this->TransformFilter->Delete();
	this->PolyData->Delete();
	this->Mapper->Delete();
	this->Property->Delete();
	this->Actor->Delete();
}

//-------------------------------------------------------------------------
void misUpviewChangesButtonRepresentation::BuildRepresentation()
{
	this->Superclass::BuildRepresentation();
}

//-------------------------------------------------------------------------
void misUpviewChangesButtonRepresentation::TurnCameraToTheLeft()
{
	this->Camera->Roll(-m_RatioChangesOfViewUp);
}


//-------------------------------------------------------------------------
void misUpviewChangesButtonRepresentation::TurnCameraToTheRight()
{
	this->Camera->Roll(m_RatioChangesOfViewUp);
}

//-------------------------------------------------------------------------
void misUpviewChangesButtonRepresentation::InitializePath()
{
}

//-------------------------------------------------------------------------
int misUpviewChangesButtonRepresentation::RenderOverlay(vtkViewport *w)
{
	int count = this->Superclass::RenderOverlay(w);
	count += this->Actor->RenderOverlay(w);
	return count;
}

//-------------------------------------------------------------------------
int misUpviewChangesButtonRepresentation::RenderOpaqueGeometry(vtkViewport *w)
{
	int count = this->Superclass::RenderOpaqueGeometry(w);
	count += this->Actor->RenderOpaqueGeometry(w);
	return count;
}

//-------------------------------------------------------------------------
int misUpviewChangesButtonRepresentation::RenderTranslucentPolygonalGeometry(vtkViewport *w)
{
	int count = this->Superclass::RenderTranslucentPolygonalGeometry(w);
	count += this->Actor->RenderTranslucentPolygonalGeometry(w);
	return count;
}

void misUpviewChangesButtonRepresentation::SetCamera( vtkCamera *camera )
{
	this->Camera = camera;
}

void misUpviewChangesButtonRepresentation::SetRatioChangesOfViewUp( double ratioChange )
{
	this->m_RatioChangesOfViewUp = ratioChange;
}