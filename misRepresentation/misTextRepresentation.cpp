#include "StdAfx.h"
#include "misTextRepresentation.h"

misTextRepresentation::misTextRepresentation(std::string name):misRepresentation(name)
{
	m_TextActor=vtkTextActor::New();
	m_Actors.push_back(m_TextActor);
}


misTextRepresentation::~misTextRepresentation(void)
{
	 this->m_TextActor->Delete();
}

void misTextRepresentation::SetText( std::string val )
{
	m_Text = val;
	this->m_TextActor->SetInput(m_Text.c_str());
}

void misTextRepresentation::SetPosition2D( double x, double y )
{
		this->m_TextActor->SetPosition(x,y);
}

 
