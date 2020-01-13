#include "stdafx.h"
#include "misImageAnnotation.h"


misImageAnnotation::misImageAnnotation()
	:misRepresentation("image annotation"), m_windowVerticalSize(0), m_windowHorizantalSize(0)
{
	m_DefaultColor[0]=1.0;
	m_DefaultColor[1]=1.0;
	m_DefaultColor[2]=0.0;
	m_DefaultFont=16;
	m_TetxureProp = vtkSmartPointer<vtkTextProperty>::New();
	m_TetxureProp->SetColor(m_DefaultColor[0],m_DefaultColor[1],m_DefaultColor[2]);
	m_TetxureProp->SetFontSize(m_DefaultFont);
	m_TetxureProp->SetFontFamily(VTK_TIMES);
}

void misImageAnnotation::SetRenWinSize(int HorizantalSize,int VerticalSize)
{
	if (HorizantalSize == 0 || VerticalSize == 0)
		return;
	m_windowHorizantalSize = HorizantalSize;
	m_windowVerticalSize = VerticalSize;
	UpdateTitlePosition();
}

void misImageAnnotation::SetTitle(std::string title)
{	
	m_leftUpActors.clear();
	std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo> annotation;
	if (m_TitleActor)
	{
		auto newEnd = std::remove(m_Actors.begin(), m_Actors.end(), m_TitleActor);
		m_Actors.erase(newEnd, m_Actors.end());
	}
	m_TitleActor = AdAnnotationMem(title,VTK_TEXT_LEFT,VTK_TEXT_TOP,m_LeftUpPosition );
	m_leftUpActors.push_back(m_TitleActor);
}

vtkSmartPointer<vtkTextActor> misImageAnnotation::AdAnnotationMem(std::string text, int justification,
                                                                  int verticalJustification, double* position)
{
	vtkSmartPointer<vtkTextActor> actor = vtkSmartPointer<vtkTextActor>::New();
	actor->SetInput(text.c_str());
	vtkSmartPointer<vtkTextProperty> prop = vtkSmartPointer<vtkTextProperty>::New();
	prop->SetColor(m_DefaultColor[0],m_DefaultColor[1],m_DefaultColor[2]);
	prop->SetFontSize(m_DefaultFont);
	actor->SetPosition(position[0],position[1]);
	actor->SetTextProperty(prop);
	prop->SetJustification(justification);
	prop->SetVerticalJustification(verticalJustification);
	m_Actors.push_back(actor);
	return actor;
}

 
void misImageAnnotation::AddDistanceAnnotaion(const double distance )
{
	std::stringstream distanceStringBuilder;
	distanceStringBuilder << distance << "mm";

	m_RightUpPosition[0] = 0.97 * m_windowHorizantalSize ;
	m_RightUpPosition[1] = 0.97 * m_windowVerticalSize  ;

	AdAnnotationMem(distanceStringBuilder.str(), VTK_TEXT_RIGHT, VTK_TEXT_TOP, m_RightUpPosition);
}

void misImageAnnotation::UpdateTitlePosition()
{
	m_LeftUpPosition[0] = 0.05 * m_windowHorizantalSize;
	m_LeftUpPosition[1] = 0.95 * m_windowVerticalSize ;	
	for_each(m_leftUpActors.begin(), m_leftUpActors.end(), [&](vtkSmartPointer<vtkTextActor> prop)
	{
		prop->SetPosition(m_LeftUpPosition);
	});
}
