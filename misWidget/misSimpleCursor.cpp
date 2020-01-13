#include "stdafx.h"
#include "misSimpleCursor.h"

#include "misStrctColorData.h"

using namespace std;

 vtkStandardNewMacro(misSimpleCursor);

misSimpleCursor::misSimpleCursor()
{
	this->DParam = 2;

	x_output = vtkPolyData::New();
	y_output = vtkPolyData::New();
	z_output = vtkPolyData::New();

	m_torus = vtkParametricTorus::New();
	ptorus = vtkParametricFunctionSource::New();

	X_Mapper = vtkPolyDataMapper::New();
	Y_Mapper = vtkPolyDataMapper::New();
	Z_Mapper = vtkPolyDataMapper::New();
	torusMapper = vtkPolyDataMapper::New();

	X_Actor = vtkActor::New();
	Y_Actor = vtkActor::New();
	Z_Actor = vtkActor::New();
	torusActor = vtkActor::New();

	m_TorusVisibility = true;
}

misSimpleCursor::~misSimpleCursor()
{
	this->X_Actor->Delete();
	this->Y_Actor->Delete();
	this->Z_Actor->Delete();

	this->X_Mapper->Delete();
	this->Y_Mapper->Delete();
	this->Z_Mapper->Delete();

}

void misSimpleCursor::SetModelBounds(double xmin, double xmax, double ymin, double ymax,double zmin, double zmax)
{
	if ( xmin != this->ModelBounds[0] || xmax != this->ModelBounds[1] ||
		ymin != this->ModelBounds[2] || ymax != this->ModelBounds[3] ||
		zmin != this->ModelBounds[4] || zmax != this->ModelBounds[5] )
	{
		this->Modified();

		this->ModelBounds[0] = xmin; this->ModelBounds[1] = xmax; 
		this->ModelBounds[2] = ymin; this->ModelBounds[3] = ymax; 
		this->ModelBounds[4] = zmin; this->ModelBounds[5] = zmax; 

		for (int i=0; i<3; i++)
		{
			if ( this->ModelBounds[2*i] > this->ModelBounds[2*i+1] )
			{
				this->ModelBounds[2*i] = this->ModelBounds[2*i+1];
			}
		}
	}
}

void misSimpleCursor::ModifyAxis()
{
	int i;

	for (i=0; i<3; i++)
	{
		if ( this->FocalPoint[i] < this->ModelBounds[2*i] )
		{
			this->FocalPoint[i] = this->ModelBounds[2*i];
		}
		if ( this->FocalPoint[i] > this->ModelBounds[2*i+1] )
		{
			this->FocalPoint[i] = this->ModelBounds[2*i+1];
		}
	}
	for(i = 0 ; i<3 ; i++)
	{
		if(this->ModelBounds[2*i] != 0)
			this->ModelBounds[2*i] = 0;
	}

	this->ModifyXAxis();
	this->ModifyYAxis();
	this->ModifyZAxis();


	// Update ourselves and release memory
	//
	this->Focus->GetPoints()->SetPoint(0,this->FocalPoint);
}

void misSimpleCursor::Initialization()
{
	this->ModifyAxis();
	//this->ModifyTorus(this->DParam);

	this->X_Mapper->SetInputData(this->Get_X());
	this->Y_Mapper->SetInputData(this->Get_Y());
	this->Z_Mapper->SetInputData(this->Get_Z());
	this->torusMapper->SetInputData(ptorus->GetOutput());
	if (this->m_initial == false)
	{
		this->m_initial = true;

		this->X_Actor->SetMapper(X_Mapper);
		X_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		this->m_Actors.push_back(X_Actor);
		this->Y_Actor->SetMapper(Y_Mapper);
		Y_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		this->m_Actors.push_back(Y_Actor);
		this->Z_Actor->SetMapper(Z_Mapper);
		Z_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		this->m_Actors.push_back(Z_Actor);
		this->torusActor->SetMapper(torusMapper);
		this->m_Actors.push_back(torusActor);

		this->UpdateCursorColor();		
	}
}

vtkPolyData * misSimpleCursor::Get_X()
{
	return x_output;
}

vtkPolyData * misSimpleCursor::Get_Y()
{
	return y_output;

}

vtkPolyData * misSimpleCursor::Get_Z()
{
	return z_output;

}

void misSimpleCursor::ModifyTorus( int radius )
{
	this->m_torus->SetRingRadius(radius);
	this->m_torus->SetCrossSectionRadius(0.05);
	this->ptorus->SetParametricFunction(this->m_torus);

	IMAGEORIENTATION orientation = this->m_WidgetOrientation;
	vtkTransform * t = vtkTransform::New();
	double pos[3];
	switch (orientation)
	{
	case AXIAL:
		break;
	case SAGITTAL:
		t->Identity();
		t->PostMultiply();
		this->torusActor->GetPosition(pos);
		t->Translate(-pos[0],-pos[1],-pos[2]);
		t->RotateY(90);
		t->Translate(pos[0],pos[1] , pos[2]);
		t->Modified();
		this->torusActor->SetUserTransform(t);
		break;
	case CORONAL:
		t->Identity();
		t->PostMultiply();
		this->torusActor->GetPosition(pos);
		t->Translate(-pos[0],-pos[1],-pos[2]);
		t->RotateX(90);
		t->Translate(pos[0],pos[1] , pos[2]);
		t->Modified();
		this->torusActor->SetUserTransform(t);
		break;
	}
}

void misSimpleCursor::ModifyXAxis()
{
	int numPts = 4;
	int numLines = 2;

	double x[3];

	vtkIdType ptIds[2];

	vtkPoints *x_newPts;
	vtkCellArray *x_newLines;

	x_newPts = vtkPoints::New();
	x_newPts->Allocate(numPts);
	x_newLines = vtkCellArray::New();
	x_newLines->Allocate(x_newLines->EstimateSize(numLines,2));

	x[0] = this->DParam ; 
	x[1] = this->ModelBounds[2]; 
	x[2] = this->ModelBounds[4];
	ptIds[0] = x_newPts->InsertNextPoint(x);

	x[0] = 5* this->DParam; 
	x[1] = this->ModelBounds[2]; 
	x[2] = this->ModelBounds[4];
	ptIds[1] =x_newPts->InsertNextPoint(x);
	x_newLines->InsertNextCell(2,ptIds);

	x[0] = -this->DParam; 
	x[1] = this->ModelBounds[2]; 
	x[2] = this->ModelBounds[4];
	ptIds[0] = x_newPts->InsertNextPoint(x);

	x[0] = -5 * this->DParam; 
	x[1] = this->ModelBounds[2]; 
	x[2] = this->ModelBounds[4];
	ptIds[1] =x_newPts->InsertNextPoint(x);
	x_newLines->InsertNextCell(2,ptIds);

	x_output->SetPoints(x_newPts);
	x_newPts->Delete();
	x_output->SetLines(x_newLines);
	x_newLines->Delete();
}

void misSimpleCursor::ModifyYAxis()
{
	int numPts = 4;
	int numLines = 2;

	vtkIdType ptIds[2];

	double y[3];

	vtkPoints *y_newPts;
	vtkCellArray *y_newLines;
	y_newPts = vtkPoints::New();
	y_newPts->Allocate(numPts);
	y_newLines = vtkCellArray::New();
	y_newLines->Allocate(y_newLines->EstimateSize(numLines,2));

	y[0] = this->ModelBounds[0]; 
	y[1] = this->DParam; 
	y[2] = this->ModelBounds[4];
	ptIds[0] = y_newPts->InsertNextPoint(y);

	y[0] = this->ModelBounds[0]; 
	y[1] = 5 * this->DParam; 
	y[2] = this->ModelBounds[4];
	ptIds[1] = y_newPts->InsertNextPoint(y);
	y_newLines->InsertNextCell(2,ptIds);

	y[0] = this->ModelBounds[0]; 
	y[1] = -this->DParam; 
	y[2] = this->ModelBounds[4];
	ptIds[0] = y_newPts->InsertNextPoint(y);

	y[0] = this->ModelBounds[0]; 
	y[1] = -5 * this->DParam; 
	y[2] = this->ModelBounds[4];
	ptIds[1] = y_newPts->InsertNextPoint(y);
	y_newLines->InsertNextCell(2,ptIds);

	y_output->SetPoints(y_newPts);
	y_newPts->Delete();
	y_output->SetLines(y_newLines);
	y_newLines->Delete();
}

void misSimpleCursor::ModifyZAxis()
{
	int numPts = 4;
	int numLines = 2;

	vtkIdType ptIds[2];
	double z[3];

	vtkPoints *z_newPts;
	vtkCellArray *z_newLines;
	z_newPts = vtkPoints::New();
	z_newPts->Allocate(numPts);
	z_newLines = vtkCellArray::New();
	z_newLines->Allocate(z_newLines->EstimateSize(numLines,2));


	z[0] = this->ModelBounds[0]; 
	z[1] = this->ModelBounds[2]; 
	z[2] = this->DParam;
	ptIds[0] = z_newPts->InsertNextPoint(z);

	z[0] = this->ModelBounds[0]; 
	z[1] = this->ModelBounds[2]; 
	z[2] = 5* this->DParam;
	ptIds[1] = z_newPts->InsertNextPoint(z);
	z_newLines->InsertNextCell(2,ptIds);


	z[0] = this->ModelBounds[0]; 
	z[1] = this->ModelBounds[2]; 
	z[2] = - this->DParam;
	ptIds[0] = z_newPts->InsertNextPoint(z);

	z[0] = this->ModelBounds[0]; 
	z[1] = this->ModelBounds[2]; 
	z[2] = -5 * this->DParam;
	ptIds[1] = z_newPts->InsertNextPoint(z);
	z_newLines->InsertNextCell(2,ptIds);

	z_output->SetPoints(z_newPts);
	z_newPts->Delete();
	z_output->SetLines(z_newLines);
	z_newLines->Delete();
}

void misSimpleCursor::UpdateCursorColor()
{
	if (!X_Actor->GetMapper())
		return;

	auto const colors = GetColorComposition();
	SetColorToActor(X_Actor, colors.XAxisColor.GetNormRgb());
	SetColorToActor(Y_Actor, colors.YAxisColor.GetNormRgb());
	SetColorToActor(Z_Actor, colors.ZAxisColor.GetNormRgb());

	misDoubleColorStruct yellowColor;
	yellowColor.SetColorToYellow();
	torusActor->GetProperty()->SetColor(yellowColor.Red, yellowColor.Green, yellowColor.Blue);
}


