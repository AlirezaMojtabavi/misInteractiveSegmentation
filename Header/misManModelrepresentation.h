#ifndef MISMANMODELREPRESENTATION_H_HEADER_INCLUDED_B7FB56C9
#define MISMANMODELREPRESENTATION_H_HEADER_INCLUDED_B7FB56C9

#include "misSurfaceRepresentation.h"

class   misManModelrepresentation: public misSurfaceRepresentation
{
public:
	
	misManModelrepresentation(std::string name);
	~misManModelrepresentation(void);
 	void  Init(double* pos,vtkRenderer*  pRenderer);
  
 
};

#endif