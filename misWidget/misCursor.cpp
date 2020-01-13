#include "stdafx.h"
#include "misCursor.h"

#include "ICornerProperties.h"

using namespace std;

misCursor::misCursor()
{
	
	auto points = vtkSmartPointer<vtkPoints>::New();
	points->vtkPoints::InsertPoint(0, 0.0, 0.0, 0.0);
	Focus->SetPoints(points);
	auto vetexes = vtkSmartPointer<vtkCellArray>::New();
	vetexes->InsertNextCell(1);
	vetexes->InsertCellPoint(0);
	Focus->SetVerts(vetexes);
	ModelBounds[0] = 0;
	ModelBounds[1] = 1.0;
	ModelBounds[2] = 0;
	ModelBounds[3] = 1.0;
	ModelBounds[4] =0;
	ModelBounds[5] = 1.0;
	FocalPoint[0] = 0.0;
	FocalPoint[1] = 0.0;
	FocalPoint[2] = 0.0;
	m_initial = false;
	SetNumberOfInputPorts(0);
}



void misCursor::SetModelBounds(double xmin, double xmax, double ymin, double ymax,double zmin, double zmax)
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

	Initialization();
}
void misCursor::SetModelBounds(double bounds[6])
{
	SetModelBounds(bounds[0], bounds[1], bounds[2], bounds[3], bounds[4],
		bounds[5]);
}

void misCursor::SetFocalPoint( double x, double y, double z )
{
	double xyz[3];
	xyz[0] = x; xyz[1] = y; xyz[2] = z;
	SetFocalPoint(xyz);
}

void misCursor::SetColorsComposition(const parcast::AxesColors& colors)
{
	m_ColorCompo = colors;
	m_initial = false;
}

void misCursor::SetColorToActor(vtkActor * actor, const parcast::Color::NormRgbType & normRgb)
{
	actor->GetProperty()->SetColor(std::get<0>(normRgb), std::get<1>(normRgb), std::get<2>(normRgb));
}

void misCursor::SetColorToActors(vtkActor * actor1, vtkActor * actor2, const parcast::Color::NormRgbType & normRgb)
{
	actor1->GetProperty()->SetColor(std::get<0>(normRgb), std::get<1>(normRgb), std::get<2>(normRgb));
	actor2->GetProperty()->SetColor(std::get<0>(normRgb), std::get<1>(normRgb), std::get<2>(normRgb));
}

parcast::AxesColors misCursor::GetColorComposition()
{
	return m_ColorCompo;
}

void misCursor::SetFocalPoint(double x[3])
{
	float telurance=5;
	if (x[0]<0 ||x[1]<0 ||x[2]<0)
	{
		return;
	}

	if ((x[0] > ModelBounds[1] +telurance)|| (x[1] > ModelBounds[3] +telurance)|| (x[2]> ModelBounds[5]+telurance))
	{
		//return;
	}
	if ( (x[0] == FocalPoint[0] )&& (x[1] == FocalPoint[1] &&
		x[2] == FocalPoint[2] ))
	{
		return;
	}

	m_CornerPropreties->SetCurrentPosition(x);
	for (int i = 0 ; i < 3 ; i++)
	{
		FocalPoint[i] = x[i];
	}
	UpdateWidgetPosition();
}

vtkSmartPointer<vtkPolyData> misCursor::GetFocus()
{
	return Focus;
}

std::vector < vtkSmartPointer<vtkActor>> misCursor::GetActors()
{
	return m_Actors;
}

bool misCursor::IsVisible( double object[3],double cameraPos[3] )
{
	double vector1[3];
	double vector2[3];
	for (int i=0;i<3;i++)
	{
		vector1[i]=FocalPoint[i]-cameraPos[i];
		vector2[i]=FocalPoint[i]-object[i];
	}
	double val=vtkMath::Dot(vector1,vector2);
	if (val<=0)
		return true;
	return  false;
}

void misCursor::SetCornerProperties(std::shared_ptr<ICornerProperties> pCornerProperties)
{
	if (pCornerProperties)
	{
		m_CornerPropreties = pCornerProperties;
	}
}

void misCursor::UpdateWidgetPosition()
{
	if (!m_CornerPropreties)
		return;

	for (auto actorItr = m_Actors.begin(); actorItr != m_Actors.end(); ++actorItr)
	{
		auto originalTransform = vtkSmartPointer<vtkMatrix4x4>::New();
		originalTransform->DeepCopy(m_CornerPropreties->GetWidgetTransform());
		const auto originPosition = m_CornerPropreties->GetWidgetPositionWithDistance(0.0);
		const auto widgetPosWithDistance = m_CornerPropreties->GetWidgetPositionWithDistance(1.0);
		originalTransform->SetElement(0, 3, widgetPosWithDistance[0]);
		originalTransform->SetElement(1, 3, widgetPosWithDistance[1]);
		originalTransform->SetElement(2, 3, widgetPosWithDistance[2]);
		FocalPoint[0] = originPosition[0];	
		FocalPoint[1] = originPosition[1];
		FocalPoint[2] = originPosition[2];
		auto transfom = vtkSmartPointer<vtkTransform>::New();
		transfom->SetMatrix(originalTransform);
		(*actorItr)->SetUserTransform(transfom);
	}
}

void misCursor::SetLineWidth( double width )
{
	m_LineWidth = width;
	m_initial = false;
}

double misCursor::GetLineWidth() const
{
	return m_LineWidth;
}