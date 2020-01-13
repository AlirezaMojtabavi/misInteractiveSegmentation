#pragma once

#include "misrepresentation.h"
#include "misSeconderyNeededHeader.h"
#include "misTrackingManagerExports.h"

//#include "d:\mis-local source\missoloution\header\misrepresentation.h"

class TRACKINGEXPORT misFrustumRepresentationForMicronTracker : public misRepresentation
{
public:
	igstkStandardClassBasicTraitsMacro( misFrustumRepresentationForMicronTracker, misRepresentation );
	static Pointer New(std::string name);

private:
	void Init();
	void InitPlanesCoordinateds();

	misItkListPointType m_PlanesCoordinateds;

public:
	misFrustumRepresentationForMicronTracker(std::string name);
	~misFrustumRepresentationForMicronTracker(void);
};

