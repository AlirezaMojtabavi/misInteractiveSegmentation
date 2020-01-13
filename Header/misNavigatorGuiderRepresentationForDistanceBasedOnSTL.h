#pragma once

//#include "misnavigatorguiderrepresentationbase.h"
#include "misNavigatorGuiderRepresentationForAngle.h"
#include "misNavigatorGuiderForDistanceBasedOnSTL.h"

class misNavigatorGuiderRepresentationForDistanceBasedOnSTL  : public misNavigatorGuiderRepresentationForAngle
{
//private:
//	misNavigatorGuiderForDistanceBasedOnSTL* m_StlActor;
	

public:
	misNavigatorGuiderRepresentationForDistanceBasedOnSTL(std::string name);
	~misNavigatorGuiderRepresentationForDistanceBasedOnSTL(void);
	igstkStandardClassBasicTraitsMacro( misNavigatorGuiderRepresentationForDistanceBasedOnSTL, misNavigatorGuiderRepresentationForAngle ); 

	static Pointer New(std::string name);

	//returns the navigator guider
	virtual misNavigatorGuiderForDistanceBasedOnSTL* GetNavigatorGuider();

	//generates guider based on type represented with input argument in string
	virtual void GenerateGuiderBasedOnType(std::string Place);

	virtual void SetGuidedNoteForFloatText(double value);

};

