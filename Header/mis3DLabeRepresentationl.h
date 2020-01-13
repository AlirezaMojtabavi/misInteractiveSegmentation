#pragma once
#include "missurfacerepresentation.h"
#include "igstkMacros.h"
#include "misVisualizationResourceManager.h"
#include "misEnums.h"
#include "vtkFollower.h"
#include "misLandmarkenums.h"
#include "misFollowerFixedArea.h"


class mis3DLabeRepresentationl :	public misSurfaceRepresentation
{
private:
 
	misFollowerFixedArea* m_textActor;
 	int  m_TextId;
public:
 igstkStandardClassBasicTraitsMacro( mis3DLabeRepresentationl, misSurfaceRepresentation )  
	typedef mis3DLabeRepresentationl                         Self;  
	typedef misSurfaceRepresentation                    Superclass; 
	typedef ::itk::SmartPointer< Self >       Pointer; 
	typedef ::itk::SmartPointer< const Self > ConstPointer; 
	static Pointer New();
	mis3DLabeRepresentationl();
	~mis3DLabeRepresentationl(void);
	void SetID(int   id,LANDMARKLABELSTAUS state );
 	

};
