#include "stdafx.h"
#include "misPreciseCursor.h"

#include "misStrctColorData.h"
#include "misPolyDataCreator.h"

vtkStandardNewMacro(misPreciseCursor);

misPreciseCursor::misPreciseCursor()
	: FarEndPos(14),
	NearEndPos(4),
	HalfNearEnd(2),
	MajorMarkingLength(0.5),
	MinorMarkingLength(0.25)
{
	DParam = 1;
}
void misPreciseCursor::ModifyAxis()
{
	//IMPORTANT NOTE
	//the cursor is set to to initial position (0, 0, 0)
	//the points are created based on Origin
	ModifyXAxis();
	ModifyYAxis();
	ModifyZAxis();

	// Update ourselves and release memory
	Focus->GetPoints()->SetPoint(0, FocalPoint);
}

void misPreciseCursor::Initialization()
{
	if (m_initial)
		return;

	m_initial = true;

	const double InsideOpacity = 0.3;
	const double OutsideOpacity = 1;
	ModifyAxis();

	m_XCone->SetRadius(GetLineWidth());
	m_XCone->SetHeight(2);
	m_XCone->SetResolution(50);
	m_YCone->SetRadius(GetLineWidth());
	m_YCone->SetHeight(2);
	m_YCone->SetResolution(50);
	m_ZCone->SetRadius(GetLineWidth());
	m_ZCone->SetHeight(2);
	m_ZCone->SetResolution(50);

	auto  x_trns =  vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	auto transformX = vtkSmartPointer<vtkTransform>::New();
	transformX->Translate(-FarEndPos - 1, 0, 0);
	transformX->RotateY(180);
	x_trns->SetInputConnection(m_XCone->GetOutputPort());
	x_trns->SetTransform(transformX);

	auto y_trns = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	auto  transformY = vtkSmartPointer<vtkTransform>::New();
	transformY->Translate(0, FarEndPos + 1, 0);
	transformY->RotateZ(90);
	y_trns->SetInputConnection(m_YCone->GetOutputPort());
	y_trns->SetTransform(transformY);

	auto z_trns = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	auto transformZ = vtkSmartPointer<vtkTransform>::New();
	transformZ->Translate(0, 0, -FarEndPos - 1);
	transformZ->RotateY(90);
	z_trns->SetInputConnection(m_ZCone->GetOutputPort());
	z_trns->SetTransform(transformZ);

	auto x_append = vtkSmartPointer<vtkAppendPolyData>::New();
	x_append->AddInputData(Get_X());
	x_append->AddInputConnection(x_trns->GetOutputPort());
	x_append->Update();

	auto y_append = vtkSmartPointer<vtkAppendPolyData>::New();;
	y_append->AddInputData(Get_Y());
	y_append->AddInputConnection(y_trns->GetOutputPort());
	y_append->Update();

	auto z_append = vtkSmartPointer<vtkAppendPolyData>::New();;
	z_append->AddInputData(Get_Z());
	z_append->AddInputConnection(z_trns->GetOutputPort());
	z_append->Update();

	m_XMapper->SetInputData(x_append->GetOutput());
	m_YMapper->SetInputData(y_append->GetOutput());
	m_ZMapper->SetInputData(z_append->GetOutput());

	m_MxMapper->SetInputData(Get_MX());
	m_MyMapper->SetInputData(Get_MY());
	m_MzMapper->SetInputData(Get_MZ());

	m_XActor->SetMapper(m_XMapper);
	m_YActor->SetMapper(m_YMapper);
	m_ZActor->SetMapper(m_ZMapper);

	m_MxActor->SetMapper(m_MxMapper);
	m_MyActor->SetMapper(m_MyMapper);
	m_MzActor->SetMapper(m_MzMapper);

	UpdateCursorColor();

	m_XActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_XActor->GetProperty()->SetOpacity(OutsideOpacity);
	m_MxActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_MxActor->GetProperty()->SetOpacity(InsideOpacity);

	m_YActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_YActor->GetProperty()->SetOpacity(OutsideOpacity);
	m_MyActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_MyActor->GetProperty()->SetOpacity(InsideOpacity);

	m_ZActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_ZActor->GetProperty()->SetOpacity(OutsideOpacity);
	m_MzActor->GetProperty()->SetLineWidth(GetLineWidth());
	m_MzActor->GetProperty()->SetOpacity(InsideOpacity);


	Initialization(m_WidgetOrientation);
}

void misPreciseCursor::Initialization(IMAGEORIENTATION type)
{
	if (type == AXIAL)
	{
		m_Actors.push_back(m_XActor);
		m_Actors.push_back(m_YActor);
		m_Actors.push_back(m_MxActor);
		m_Actors.push_back(m_MyActor);
	}
	else if (type == CORONAL)
	{
		m_Actors.push_back(m_XActor);
		m_Actors.push_back(m_ZActor);
		m_Actors.push_back(m_MxActor);
		m_Actors.push_back(m_MzActor);
	}
	else if (type == SAGITTAL)
	{
		m_Actors.push_back(m_YActor);
		m_Actors.push_back(m_ZActor);
		m_Actors.push_back(m_MyActor);
		m_Actors.push_back(m_MzActor);
	}
	else if (type == UNKnownDirection)
	{
		m_Actors.push_back(m_XActor);
		m_Actors.push_back(m_YActor);
		m_Actors.push_back(m_ZActor);
		m_Actors.push_back(m_MxActor);
		m_Actors.push_back(m_MyActor);
		m_Actors.push_back(m_MzActor);
	}
}

vtkSmartPointer<vtkPolyData>  misPreciseCursor::Get_X() const
{
	return x_output;
}

vtkSmartPointer<vtkPolyData> misPreciseCursor::Get_Y() const
{
	return y_output;
}

vtkSmartPointer<vtkPolyData> misPreciseCursor::Get_Z() const
{
	return z_output;
}

vtkSmartPointer<vtkPolyData> misPreciseCursor::Get_MX() const
{
	return Mx_output;
}

vtkSmartPointer<vtkPolyData> misPreciseCursor::Get_MY() const
{
	return My_output;
}

vtkSmartPointer<vtkPolyData> misPreciseCursor::Get_MZ() const
{
	return Mz_output;
}



void misPreciseCursor::ModifyXAxis()
{
	const double MarkingLength = GetLineWidth() * MajorMarkingLength;
	misPolyDataCreator polyDataCreator(10, 20);
	polyDataCreator.InsertLine(NearEndPos, 0, 0, FarEndPos, 0, 0);
	polyDataCreator.InsertLine(-NearEndPos, 0, 0, -FarEndPos, 0, 0);
	polyDataCreator.InsertLine(NearEndPos, MarkingLength, 0, NearEndPos, -MarkingLength, 0);
	polyDataCreator.InsertLine(NearEndPos, 0, MarkingLength, NearEndPos, 0, -MarkingLength);
	polyDataCreator.InsertLine(FarEndPos, MarkingLength, 0, FarEndPos, -MarkingLength, 0);
	polyDataCreator.InsertLine(FarEndPos, 0, MarkingLength, FarEndPos, 0, -MarkingLength);
	polyDataCreator.InsertLine(-NearEndPos, MarkingLength, 0, -NearEndPos, -MarkingLength, 0);
	polyDataCreator.InsertLine(-NearEndPos, 0, MarkingLength, -NearEndPos, 0, -MarkingLength);
	polyDataCreator.InsertLine(-FarEndPos, MarkingLength, 0, -FarEndPos, -MarkingLength, 0);
	polyDataCreator.InsertLine(-FarEndPos, 0, MarkingLength, -FarEndPos, 0, -MarkingLength);
	polyDataCreator.ApplyToPolyData(x_output);

	ModifyMeasurmentXAxis();
}

void misPreciseCursor::ModifyYAxis()
{
	const double MarkingLength = GetLineWidth() * MajorMarkingLength;
	misPolyDataCreator polyDataCreator(10, 20);
	polyDataCreator.InsertLine(0, NearEndPos, 0, 0, FarEndPos, 0);
	polyDataCreator.InsertLine(0, -NearEndPos, 0, 0, -FarEndPos, 0);
	polyDataCreator.InsertLine(MarkingLength, NearEndPos, 0, -MarkingLength, NearEndPos, 0);
	polyDataCreator.InsertLine(0, NearEndPos, MarkingLength, 0, NearEndPos, -MarkingLength);
	polyDataCreator.InsertLine(MarkingLength, FarEndPos, 0, -MarkingLength, FarEndPos, 0);
	polyDataCreator.InsertLine(0, FarEndPos, MarkingLength, 0, FarEndPos, -MarkingLength);
	polyDataCreator.InsertLine(MarkingLength, -NearEndPos, 0, -MarkingLength, -NearEndPos, 0);
	polyDataCreator.InsertLine(0, -NearEndPos, MarkingLength, 0, -NearEndPos, -MarkingLength);
	polyDataCreator.InsertLine(MarkingLength, -FarEndPos, 0, -MarkingLength, -FarEndPos, 0);
	polyDataCreator.InsertLine(0, -FarEndPos, MarkingLength, 0, -FarEndPos, -MarkingLength);
	polyDataCreator.ApplyToPolyData(y_output);

	ModifyMeasurmentYAxis();
}

void misPreciseCursor::ModifyZAxis()
{
	const double MarkingLength = GetLineWidth() * MajorMarkingLength;
	misPolyDataCreator polyDataCreator(10, 20);
	polyDataCreator.InsertLine(0, 0, NearEndPos, 0, 0, FarEndPos);
	polyDataCreator.InsertLine(0, 0, -NearEndPos, 0, 0, -FarEndPos);
	polyDataCreator.InsertLine(MarkingLength, 0, NearEndPos, -MarkingLength, 0, NearEndPos);
	polyDataCreator.InsertLine(0, MarkingLength, NearEndPos, 0, -MarkingLength, NearEndPos);
	polyDataCreator.InsertLine(MarkingLength, 0, FarEndPos, -MarkingLength, 0, FarEndPos);
	polyDataCreator.InsertLine(0, MarkingLength, FarEndPos, 0, -MarkingLength, FarEndPos);
	polyDataCreator.InsertLine(MarkingLength, 0, -NearEndPos, -MarkingLength, 0, -NearEndPos);
	polyDataCreator.InsertLine(0, MarkingLength, -NearEndPos, 0, -MarkingLength, -NearEndPos);
	polyDataCreator.InsertLine(MarkingLength, 0, -FarEndPos, -MarkingLength, 0, -FarEndPos);
	polyDataCreator.InsertLine(0, MarkingLength, -FarEndPos, 0, -MarkingLength, -FarEndPos);
	polyDataCreator.ApplyToPolyData(z_output);

	ModifyMeasurmentZAxis();
}

void misPreciseCursor::ModifyMeasurmentXAxis()
{
	const double MarkingLength = GetLineWidth() * MinorMarkingLength;
	misPolyDataCreator polyDataCreator(5, 10);
	polyDataCreator.InsertLine(-NearEndPos, 0, 0, NearEndPos, 0, 0);
	polyDataCreator.InsertLine(HalfNearEnd, MarkingLength, 0, HalfNearEnd, -MarkingLength, 0);
	polyDataCreator.InsertLine(HalfNearEnd, 0, MarkingLength, HalfNearEnd, 0, -MarkingLength);
	polyDataCreator.InsertLine(-HalfNearEnd, MarkingLength, 0, -HalfNearEnd, -MarkingLength, 0);
	polyDataCreator.InsertLine(-HalfNearEnd, 0, MarkingLength, -HalfNearEnd, 0, -MarkingLength);
	polyDataCreator.ApplyToPolyData(Mx_output);
}

void misPreciseCursor::ModifyMeasurmentYAxis()
{
	const double MarkingLength = GetLineWidth() * MinorMarkingLength;
	misPolyDataCreator polyDataCreator(5, 10);
	polyDataCreator.InsertLine(0, -NearEndPos, 0, 0, NearEndPos, 0);
	polyDataCreator.InsertLine(MarkingLength, HalfNearEnd, 0, -MarkingLength, HalfNearEnd, 0);
	polyDataCreator.InsertLine(0, HalfNearEnd, MarkingLength, 0, HalfNearEnd, -MarkingLength);
	polyDataCreator.InsertLine(MarkingLength, -HalfNearEnd, 0, -MarkingLength, -HalfNearEnd, 0);
	polyDataCreator.InsertLine(0, -HalfNearEnd, MarkingLength, 0, -HalfNearEnd, -MarkingLength);
	polyDataCreator.ApplyToPolyData(My_output);
}

void misPreciseCursor::ModifyMeasurmentZAxis()
{
	const double MarkingLength = GetLineWidth() * MinorMarkingLength;
	misPolyDataCreator polyDataCreator(5, 10);
	polyDataCreator.InsertLine(0, 0, -NearEndPos, 0, 0, NearEndPos);
	polyDataCreator.InsertLine(MarkingLength, 0, HalfNearEnd, -MarkingLength, 0, HalfNearEnd);
	polyDataCreator.InsertLine(0, MarkingLength, HalfNearEnd, 0, -MarkingLength, HalfNearEnd);
	polyDataCreator.InsertLine(MarkingLength, 0, -HalfNearEnd, -MarkingLength, 0, -HalfNearEnd);
	polyDataCreator.InsertLine(0, MarkingLength, -HalfNearEnd, 0, -MarkingLength, -HalfNearEnd);
	polyDataCreator.ApplyToPolyData(Mz_output);
}

void misPreciseCursor::UpdateCursorColor()
{
	if (!m_XActor->GetMapper())
		return;

	auto const colors = GetColorComposition();
	SetColorToActors(m_XActor, m_MxActor, colors.XAxisColor.GetNormRgb());
	SetColorToActors(m_YActor, m_MyActor, colors.YAxisColor.GetNormRgb());
	SetColorToActors(m_ZActor, m_MzActor, colors.ZAxisColor.GetNormRgb());
}