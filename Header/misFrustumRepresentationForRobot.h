#pragma once

#include "misrepresentation.h"
#include "misSeconderyNeededHeader.h"

class misFrustumRepresentationForRobot : public misRepresentation
{
public:
	igstkStandardAbstractClassTraitsMacro( misFrustumRepresentationForRobot, misRepresentation ) ;
	static Pointer New(std::string name);

private:
	void Init();
	void InitPlanesCoordinateds();

	misItkListPointType m_PlanesCoordinateds;

public:
	misFrustumRepresentationForRobot(std::string name);
	~misFrustumRepresentationForRobot(void);
};

