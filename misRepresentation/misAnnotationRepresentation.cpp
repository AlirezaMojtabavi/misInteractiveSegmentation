#include "StdAfx.h"
#include "misAnnotationRepresentation.h"

using std::string;

misAnnotationRepresentation::misAnnotationRepresentation(string name) :misRepresentation(name)
, m_TextActor(vtkSmartPointer<vtkTextActor>::New())
 {
	m_WindooSize[0] = 0;
	m_WindooSize[1] = 0;

	m_Actors.push_back(m_TextActor);
}
 

 
void misAnnotationRepresentation::SetNormalizedPosition(double x, double y)
{

	double xpos = x * m_WindooSize[0];
	double ypos = y * m_WindooSize[0];
	this->SetPosition(xpos, ypos);

}

tgt::vec2 misAnnotationRepresentation::WindowSize() const
{
	return m_WindooSize;
}

void misAnnotationRepresentation::WindowSize(tgt::vec2 val)
{
	m_WindooSize = val;
	double 	x = m_WindooSize[0] * m_NormalizedPosition[0];
	double 	y = m_WindooSize[1] * m_NormalizedPosition[1];
	this->SetPosition(x, y);
}

void misAnnotationRepresentation::SetPosition(double x, double y)
{

	m_TextActor->SetPosition(x, y);
	if ((m_WindooSize[0] != 0) && (m_WindooSize[1] != 0))
	{
		m_NormalizedPosition[0] = x / m_WindooSize[0];
		m_NormalizedPosition[1] = y / m_WindooSize[1];
	}

}

void misAnnotationRepresentation::SetText(std::string val)
{
	vtkSmartPointer<vtkTextProperty> property = vtkSmartPointer<vtkTextProperty>::New();
	property->SetColor(0, 1, 1);
	property->SetFontSize(10);
	m_TextActor->SetInput(val.c_str());
	m_TextActor->SetTextProperty(property);

}



