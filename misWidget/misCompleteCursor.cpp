#include "stdafx.h"
#include "misCompleteCursor.h"

using namespace std;

vtkStandardNewMacro(misCompleteCursor);

misCompleteCursor::misCompleteCursor()
{
	x_output = vtkPolyData::New();
	y_output = vtkPolyData::New();
	z_output = vtkPolyData::New();
	X_Mapper = vtkPolyDataMapper::New();
	Y_Mapper = vtkPolyDataMapper::New();
	Z_Mapper = vtkPolyDataMapper::New();

	X_Actor = vtkActor::New();
	Y_Actor = vtkActor::New();
	Z_Actor = vtkActor::New();
	m_TorusVisibility = false;
}

misCompleteCursor::~misCompleteCursor()
{
	X_Actor->Delete();
	Y_Actor->Delete();
	Z_Actor->Delete();
	X_Mapper->Delete();
	Y_Mapper->Delete();
	Z_Mapper->Delete();
}

void misCompleteCursor::SetModelBounds(double xmin, double xmax, double ymin, double ymax,double zmin, double zmax)
{
	if ( xmin != ModelBounds[0] || xmax != ModelBounds[1] ||
		ymin != ModelBounds[2] || ymax != ModelBounds[3] ||
		zmin != ModelBounds[4] || zmax != ModelBounds[5] )
	{
		Modified();

		ModelBounds[0] = xmin; ModelBounds[1] = xmax; 
		ModelBounds[2] = ymin; ModelBounds[3] = ymax; 
		ModelBounds[4] = zmin; ModelBounds[5] = zmax; 

		for (int i=0; i<3; i++)
		{
			if ( ModelBounds[2*i] > ModelBounds[2*i+1] )
			{
				ModelBounds[2*i] = ModelBounds[2*i+1];
			}
		}
	}
}

void misCompleteCursor::ModifyAxis()
{
	for (int i=0; i<3; i++)
	{
		if ( FocalPoint[i] < ModelBounds[2*i] )
		{
			FocalPoint[i] = ModelBounds[2*i];
		}
		if ( FocalPoint[i] > ModelBounds[2*i+1] )
		{
			FocalPoint[i] = ModelBounds[2*i+1];
		}
	}

	ModifyXAxis();
	ModifyYAxis();
	ModifyZAxis();

	Focus->GetPoints()->SetPoint(0,FocalPoint);
}

void misCompleteCursor::ModifyBoundingBox()
{
	int b_numPts=0, b_numLines=0;

	vtkPoints *newPts=NULL;
	vtkCellArray *newLines=NULL;

	double x[3]={0,0,0};
	vtkIdType ptIds[2]={0,0};


	b_numPts += 8;
	b_numLines += 12;


	if ( b_numPts ) 
	{
		newPts = vtkPoints::New();
		newPts->Allocate(b_numPts);
		newLines = vtkCellArray::New();
		newLines->Allocate(newLines->EstimateSize(b_numLines,2));
	}
	else
	{
		return;
	}


	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[4];
	ptIds[0] = newPts->InsertNextPoint(x);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[4];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[4];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	// Second triad
	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[5];
	ptIds[0] = newPts->InsertNextPoint(x);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[4];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	// Fill in remaining lines
	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[4];
	ptIds[0] = newPts->InsertNextPoint(x);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[4];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[4];
	ptIds[0] = newPts->InsertNextPoint(x);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[4];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);


	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[5];
	ptIds[0] = newPts->InsertNextPoint(x);

	x[0] = ModelBounds[1]; 
	x[1] = ModelBounds[2]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	x[0] = ModelBounds[0]; 
	x[1] = ModelBounds[3]; 
	x[2] = ModelBounds[5];
	ptIds[1] = newPts->InsertNextPoint(x);
	newLines->InsertNextCell(2,ptIds);

	newPts->Delete();
	newLines->Delete();
}

vtkPolyData * misCompleteCursor::Get_X()
{
	return x_output;
}

vtkPolyData * misCompleteCursor::Get_Y()
{
	return y_output;
}

vtkPolyData * misCompleteCursor::Get_Z()
{
	return z_output;
}

 void misCompleteCursor::Initialization()
{
	ModifyAxis();
	ModifyBoundingBox();

	X_Mapper->SetInputData(Get_X());
	Y_Mapper->SetInputData(Get_Y());
	Z_Mapper->SetInputData(Get_Z());

	if (m_initial == false)
	{
		m_initial = true;

		X_Actor->SetMapper(X_Mapper);
		X_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		vtkTransform* XTransform = vtkTransform::New();
		XTransform->Identity();
		X_Actor->SetUserTransform(XTransform);
		m_Actors.push_back(X_Actor);

		Y_Actor->SetMapper(Y_Mapper);
		Y_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		vtkTransform* YTransform = vtkTransform::New();
		YTransform->Identity();
		Y_Actor->SetUserTransform(YTransform);
		m_Actors.push_back(Y_Actor);

		Z_Actor->SetMapper(Z_Mapper);
		Z_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		vtkTransform* ZTransform = vtkTransform::New();
		ZTransform->Identity();
		Z_Actor->SetUserTransform(ZTransform);
		m_Actors.push_back(Z_Actor);
		UpdateCursorColor();	
	}
}

void misCompleteCursor::UpdateCursorColor()
{
	if (!X_Actor->GetMapper())
		return;

	auto const colors = GetColorComposition();
	SetColorToActor(X_Actor, colors.XAxisColor.GetNormRgb());
	SetColorToActor(Y_Actor, colors.YAxisColor.GetNormRgb());
	SetColorToActor(Z_Actor, colors.ZAxisColor.GetNormRgb());
}

bool misCompleteCursor::IsVisible( double object[3],double cameraPos[3] )
{
	bool res1,res2;
	res1=misCursor::IsVisible(object,cameraPos);

	double vector1[3]={0,0,0};
	double vector2[3]={0,0,0};

	double  posXActor[3];
	X_Actor->GetPosition(posXActor);
	for (int i=0;i<3;i++)

	{
		vector1[i]=posXActor[i]-cameraPos[i];
		vector2[i]=posXActor[i]-object[i];
	}
	double val=vtkMath::Dot(vector1,vector2);
	if (val<=0)
		res2= true;
	else
		res2=false;
	return res1&&res2;
}

void misCompleteCursor::ModifyXAxis()
{
	int numPts = 2;
	int numLines = 1;

	vtkPoints *x_newPts=NULL;
	vtkCellArray *x_newLines=NULL;
	x_newPts = vtkPoints::New();
	x_newPts->Allocate(numPts);
	x_newLines = vtkCellArray::New();
	x_newLines->Allocate(x_newLines->EstimateSize(numLines,2));

	double x[3]={0,0,0};
	vtkIdType ptIds[2]={0,0};

	x[0] = ModelBounds[0]; 
	x[1] = 0.0; 
	x[2] = 0.0;
	ptIds[0] = x_newPts->InsertNextPoint(x);

	x[0] = ModelBounds[1]; 
	x[1] = 0.0; 
	x[2] = 0.0;
	ptIds[1] =x_newPts->InsertNextPoint(x);
	x_newLines->InsertNextCell(2,ptIds);

	x_output->SetPoints(x_newPts);
	x_newPts->Delete();
	x_output->SetLines(x_newLines);
	x_newLines->Delete();

}

void misCompleteCursor::ModifyYAxis()
{
	int numPts = 2;
	int numLines = 1;

	vtkPoints *y_newPts=NULL;
	vtkCellArray *y_newLines=NULL;
	y_newPts = vtkPoints::New();
	y_newPts->Allocate(numPts);
	y_newLines = vtkCellArray::New();
	y_newLines->Allocate(y_newLines->EstimateSize(numLines,2));

	double y[3]={0,0,0};
	vtkIdType ptIds[2]={0,0};

	y[0] = 0.0; 
	y[1] = ModelBounds[2]; 
	y[2] = 0.0;
	ptIds[0] = y_newPts->InsertNextPoint(y);

	y[0] = 0.0; 
	y[1] = ModelBounds[3]; 
	y[2] = 0.0;
	ptIds[1] = y_newPts->InsertNextPoint(y);
	y_newLines->InsertNextCell(2,ptIds);

	y_output->SetPoints(y_newPts);
	y_newPts->Delete();
	y_output->SetLines(y_newLines);
	y_newLines->Delete();
}

void misCompleteCursor::ModifyZAxis()
{
	int numPts = 2;
	int numLines = 1;

	vtkPoints *z_newPts=NULL;
	vtkCellArray *z_newLines=NULL;
	z_newPts = vtkPoints::New();
	z_newPts->Allocate(numPts);
	z_newLines = vtkCellArray::New();
	z_newLines->Allocate(z_newLines->EstimateSize(numLines,2));

	double z[3]={0,0,0};
	vtkIdType ptIds[2]={0,0};

	z[0] = 0.0; 
	z[1] = 0.0; 
	z[2] = ModelBounds[4];
	ptIds[0] = z_newPts->InsertNextPoint(z);

	z[0] = 0.0; 
	z[1] = 0.0; 
	z[2] = ModelBounds[5];
	ptIds[1] = z_newPts->InsertNextPoint(z);
	z_newLines->InsertNextCell(2,ptIds);

	z_output->SetPoints(z_newPts);
	z_newPts->Delete();
	z_output->SetLines(z_newLines);
	z_newLines->Delete();
}