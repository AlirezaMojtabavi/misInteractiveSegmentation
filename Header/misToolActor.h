#pragma once
#include "vtkactor.h"

class misToolActor :
	public vtkActor
{
public:

	static  misToolActor* New();
	misToolActor(void);
	~misToolActor(void);
};
