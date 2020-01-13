#pragma once

#include "misRepresentation.h"

class misAnnoatationGroupRep:public misRepresentation
{
private:
	misAnnoatationGroupRep(std::string name);
public:
	typedef misAnnoatationGroupRep                         Self;  
	typedef misRepresentation                    Superclass; 
	typedef ::itk::SmartPointer< Self >       Pointer; 
	typedef ::itk::SmartPointer< const Self > ConstPointer; 
	static Pointer New(std::string name); 

	~misAnnoatationGroupRep(void);
	void AddActors(std::vector<vtkSmartPointer<vtkTextActor>> pActorList);
};

