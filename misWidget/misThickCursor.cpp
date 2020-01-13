#include "StdAfx.h"
#include "misThickCursor.h"

#include "misStrctColorData.h"

 vtkStandardNewMacro(misThickCursor);

misThickCursor::misThickCursor(void)
{
	DParam = 7;

	RX_Mapper = vtkPolyDataMapper::New();
	RY_Mapper = vtkPolyDataMapper::New();
	RZ_Mapper = vtkPolyDataMapper::New();

	LX_Mapper = vtkPolyDataMapper::New();
	LY_Mapper = vtkPolyDataMapper::New();
	LZ_Mapper = vtkPolyDataMapper::New();

	SphereSource = vtkSphereSource::New();
	SphereMapper = vtkPolyDataMapper::New();

	RX_Actor = vtkActor::New();
	RY_Actor = vtkActor::New();
	RZ_Actor = vtkActor::New();

	LX_Actor = vtkActor::New();
	LY_Actor = vtkActor::New();
	LZ_Actor = vtkActor::New();

	SphereActor = vtkActor::New();
}

misThickCursor::~misThickCursor(void)
{
	RX_Actor->Delete();
	RY_Actor->Delete();
	RZ_Actor->Delete();

	LX_Actor->Delete();
	LY_Actor->Delete();
	LZ_Actor->Delete();

	SphereActor->Delete();

	RX_Mapper->Delete();
	RY_Mapper->Delete();
	RZ_Mapper->Delete();

	LX_Mapper->Delete();
	LY_Mapper->Delete();
	LZ_Mapper->Delete();

	SphereMapper->Delete();
	SphereSource->Delete();
}

void misThickCursor::SetModelBounds(double xmin, double xmax, double ymin, double ymax,double zmin, double zmax)
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

void misThickCursor::ModifyAxis()
{
	int i;

	for (i=0; i<3; i++)
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
	for(i = 0 ; i<3 ; i++)
	{
		if(ModelBounds[2*i] != 0)
			ModelBounds[2*i] = 0;
	}

	ModifyXAxis();
	ModifyYAxis();
	ModifyZAxis();


	// Update ourselves and release memory
	//
	Focus->GetPoints()->SetPoint(0,FocalPoint);
}

void misThickCursor::Initialization()
{
	ModifyAxis();
	ModifySphere();

	RX_Mapper->SetInputConnection(Get_RX());
	RY_Mapper->SetInputConnection(Get_RY());
	RZ_Mapper->SetInputConnection(Get_RZ());

	LX_Mapper->SetInputConnection(Get_LX());
	LY_Mapper->SetInputConnection(Get_LY());
	LZ_Mapper->SetInputConnection(Get_LZ());

	SphereMapper->SetInputConnection(SphereSource->GetOutputPort());
	if (m_initial == false)
	{
		m_initial = true;

		RX_Actor->SetMapper(RX_Mapper);
		m_Actors.push_back(RX_Actor);
		RY_Actor->SetMapper(RY_Mapper);
		m_Actors.push_back(RY_Actor);
		RZ_Actor->SetMapper(RZ_Mapper);
		m_Actors.push_back(RZ_Actor);

		LX_Actor->SetMapper(LX_Mapper);
		m_Actors.push_back(LX_Actor);
		LY_Actor->SetMapper(LY_Mapper);
		m_Actors.push_back(LY_Actor);
		LZ_Actor->SetMapper(LZ_Mapper);
		m_Actors.push_back(LZ_Actor);

		RX_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		RY_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		RZ_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		LX_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		LY_Actor->GetProperty()->SetLineWidth(GetLineWidth());
		LZ_Actor->GetProperty()->SetLineWidth(GetLineWidth());

		SphereActor->SetMapper(SphereMapper);
		m_Actors.push_back(SphereActor);


		UpdateCursorColor();
	}
}

vtkAlgorithmOutput * misThickCursor::Get_RX()
{
	return Rx_output;
}

vtkAlgorithmOutput * misThickCursor::Get_RY()
{
	return Ry_output;

}

vtkAlgorithmOutput * misThickCursor::Get_RZ()
{
	return Rz_output;

}

vtkAlgorithmOutput * misThickCursor::Get_LX()
{
	return Lx_output;
}

vtkAlgorithmOutput * misThickCursor::Get_LY()
{
	return Ly_output;

}

vtkAlgorithmOutput * misThickCursor::Get_LZ()
{
	return Lz_output;

}

void misThickCursor::ModifySphere()
{
	double center_x = ModelBounds[0];
	double center_y = ModelBounds[2];
	double center_z = ModelBounds[4];

	SphereSource->SetCenter(center_x , center_y , center_z);
	SphereSource->SetRadius(GetLineWidth());
	SphereSource->SetThetaResolution(100);
	SphereSource->SetPhiResolution(100);
	SphereSource->Modified();

}

void misThickCursor::ModifyXAxis()
{
	vtkLineSource* Xr_LineSource = vtkLineSource::New();
	Xr_LineSource->SetResolution(5);

	vtkTubeFilter* Xr_TubeSource = vtkTubeFilter::New();
	Xr_TubeSource->SetRadius(GetLineWidth());
	Xr_TubeSource->SetNumberOfSides(30);
	Xr_TubeSource->SetInputConnection(Xr_LineSource->GetOutputPort());

	double P1[3] , P2[3];

	P1[0] = DParam; 
	P1[1] = ModelBounds[2];
	P1[2] = ModelBounds[4];

	P2[0] = 5* DParam; 
	P2[1] = ModelBounds[2];
	P2[2] = ModelBounds[4];

	Xr_LineSource->SetPoint1(P1);
	Xr_LineSource->SetPoint2(P2);

	Rx_output = Xr_TubeSource->GetOutputPort();

	vtkLineSource* Xl_LineSource = vtkLineSource::New();
	Xl_LineSource->SetResolution(5);

	vtkTubeFilter* Xl_TubeSource = vtkTubeFilter::New();
	Xl_TubeSource->SetRadius(GetLineWidth());
	Xl_TubeSource->SetNumberOfSides(30);
	Xl_TubeSource->SetInputConnection(Xl_LineSource->GetOutputPort());

	P1[0] = -DParam; 
	P1[1] = ModelBounds[2];
	P1[2] = ModelBounds[4];

	P2[0] = -5 * DParam; 
	P2[1] = ModelBounds[2];
	P2[2] = ModelBounds[4];

	Xl_LineSource->SetPoint1(P1);
	Xl_LineSource->SetPoint2(P2);

	Lx_output = Xl_TubeSource->GetOutputPort();


}

void misThickCursor::ModifyYAxis()
{
	vtkLineSource* Yr_LineSource = vtkLineSource::New();
	Yr_LineSource->SetResolution(5);

	vtkTubeFilter* Yr_TubeSource = vtkTubeFilter::New();
	Yr_TubeSource->SetRadius(GetLineWidth());
	Yr_TubeSource->SetNumberOfSides(30);
	Yr_TubeSource->SetInputConnection(Yr_LineSource->GetOutputPort());

	double P1[3] , P2[3];

	P1[0] = ModelBounds[0];
	P1[1] = DParam; 
	P1[2] = ModelBounds[4];

	P2[0] = ModelBounds[0]; 
	P2[1] = 5 * DParam; 
	P2[2] = ModelBounds[4];

	Yr_LineSource->SetPoint1(P1);
	Yr_LineSource->SetPoint2(P2);

	Ry_output = Yr_TubeSource->GetOutputPort();

	vtkLineSource* Yl_LineSource = vtkLineSource::New();
	Yl_LineSource->SetResolution(5);

	vtkTubeFilter* Yl_TubeSource = vtkTubeFilter::New();
	Yl_TubeSource->SetRadius(GetLineWidth());
	Yl_TubeSource->SetNumberOfSides(30);
	Yl_TubeSource->SetInputConnection(Yl_LineSource->GetOutputPort());

	P1[0] = ModelBounds[0];
	P1[1] = -DParam; 
	P1[2] = ModelBounds[4];

	P2[0] = ModelBounds[0]; 
	P2[1] = -5 * DParam; 
	P2[2] = ModelBounds[4];

	Yl_LineSource->SetPoint1(P1);
	Yl_LineSource->SetPoint2(P2);

	Ly_output = Yl_TubeSource->GetOutputPort();

	// 	Y_LineSource->Delete();
	// 	Y_TubeSource->Delete();
}

void misThickCursor::ModifyZAxis()
{
	vtkLineSource* Zr_LineSource = vtkLineSource::New();
	Zr_LineSource->SetResolution(5);

	vtkTubeFilter* Zr_TubeSource = vtkTubeFilter::New();
	Zr_TubeSource->SetNumberOfSides(30);
	Zr_TubeSource->SetRadius(GetLineWidth());
	Zr_TubeSource->SetInputConnection(Zr_LineSource->GetOutputPort());

	double P1[3] , P2[3];

	P1[0] = ModelBounds[0]; 
	P1[1] = ModelBounds[2]; 
	P1[2] = DParam;

	P2[0] = ModelBounds[0]; 
	P2[1] = ModelBounds[2]; 
	P2[2] = 5* DParam;

	Zr_LineSource->SetPoint1(P1);
	Zr_LineSource->SetPoint2(P2);

	Rz_output = Zr_TubeSource->GetOutputPort();

	vtkLineSource* Zl_LineSource = vtkLineSource::New();
	Zl_LineSource->SetResolution(5);

	vtkTubeFilter* Zl_TubeSource = vtkTubeFilter::New();
	Zl_TubeSource->SetNumberOfSides(30);
	Zl_TubeSource->SetRadius(GetLineWidth());
	Zl_TubeSource->SetInputConnection(Zl_LineSource->GetOutputPort());

	P1[0] = ModelBounds[0]; 
	P1[1] = ModelBounds[2]; 
	P1[2] = -DParam;

	P2[0] = ModelBounds[0]; 
	P2[1] = ModelBounds[2]; 
	P2[2] = -5* DParam;

	Zl_LineSource->SetPoint1(P1);
	Zl_LineSource->SetPoint2(P2);

	Lz_output = Zl_TubeSource->GetOutputPort();
}

void misThickCursor::UpdateCursorColor()
{
	if (!RX_Actor->GetMapper())
		return;

	auto const colors = GetColorComposition();
	SetColorToActors(RX_Actor, LX_Actor, colors.XAxisColor.GetNormRgb());
	SetColorToActors(RY_Actor, LY_Actor, colors.YAxisColor.GetNormRgb());
	SetColorToActors(RZ_Actor, LZ_Actor, colors.ZAxisColor.GetNormRgb());

	misDoubleColorStruct yellowColor;
	yellowColor.SetColorToYellow();
	SphereActor->GetProperty()->SetColor(yellowColor.Red, yellowColor.Green, yellowColor.Blue);
	SphereActor->GetProperty()->SetAmbient(1.0);
	RX_Actor->GetProperty()->SetAmbient(1.0);
	RY_Actor->GetProperty()->SetAmbient(1.0);
	RZ_Actor->GetProperty()->SetAmbient(1.0);
	LX_Actor->GetProperty()->SetAmbient(1.0);
	LY_Actor->GetProperty()->SetAmbient(1.0);
	LZ_Actor->GetProperty()->SetAmbient(1.0);
}