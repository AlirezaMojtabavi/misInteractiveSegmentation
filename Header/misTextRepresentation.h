#pragma once
#include "misRepresentation.h"
class misTextRepresentation :
	public misRepresentation
{
private:
	vtkTextActor* m_TextActor;
	std::string m_Text;
	
public:
	typedef misTextRepresentation                         Self;  
	typedef misOldObject                    Superclass; 
	typedef ::itk::SmartPointer< Self >       Pointer; 
	typedef ::itk::SmartPointer< const Self > ConstPointer; 
	static Pointer New(std::string name); 
	misTextRepresentation(std::string name);
	void SetText(std::string val);
	void SetPosition2D(double x, double y);
	~misTextRepresentation(void);
	
};

