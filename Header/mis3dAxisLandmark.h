#pragma once
#include "missurfacerepresentation.h"
#include "igstkMacros.h"
class mis3dAxisLandmark :
	public misSurfaceRepresentation
{
protected:
	mis3dAxisLandmark();

	void AddZline();

	void AddYLine();

	void AddXLine();
public :
	~mis3dAxisLandmark(void);


	igstkStandardClassBasicTraitsMacro( mis3dAxisLandmark, misSurfaceRepresentation )  
		static Pointer New( );
};

