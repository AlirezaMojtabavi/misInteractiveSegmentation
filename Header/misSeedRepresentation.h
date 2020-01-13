#pragma once

#include "misLandmarkPointerRepresentation.h"

class misSeedRepresentation : 	public misLandmarkPointerRepresentation
{
private:
    void  UpdateLabelWithCategory(void );

public:
	igstkStandardClassBasicTraitsMacro( misSeedRepresentation, misLandmarkPointerRepresentation  )  
	static Pointer New(std::string name);
	misSeedRepresentation(std::string name);
	~misSeedRepresentation(void);

	virtual void UpdateData(LANDMARKLABELSTAUS landmarkStatus);
	
};
