#pragma once
#include "misrepresentation.h"

class misAnnotationRepresentation : 	public misRepresentation
{

public:
	misAnnotationRepresentation(std::string name);


	void SetText(std::string val);
	void SetPosition(double x, double y);
	void SetNormalizedPosition(double x, double y);
	tgt::vec2 WindowSize() const;
	void WindowSize(tgt::vec2 val);

private:

	tgt::vec2   m_WindooSize;
	tgt::vec2   m_NormalizedPosition;
	vtkSmartPointer<vtkTextActor>  m_TextActor;
	
};

