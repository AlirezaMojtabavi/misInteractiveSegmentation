#pragma once

#include "misRepresentation.h"
#include "misSeconderyNeededHeader.h"

class  misFrustumRepresentation : public misRepresentation
{
public:
   igstkStandardAbstractClassTraitsMacro( misFrustumRepresentation, misRepresentation ) ;
   static Pointer New(std::string name);
 
private:
	void Init();
	void InitPlanesCoordinateds();

	misItkListPointType m_PlanesCoordinateds;

public:

	misFrustumRepresentation(std::string name);
	~misFrustumRepresentation(void);
};
