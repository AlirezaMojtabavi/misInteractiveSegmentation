#pragma once
#include "missurfacerepresentation.h"
#include "vtkLineSource.h"
#include "vtkTextActor.h"
#include "vtkTubeFilter.h"
class misNavigatorGuider;

#define TubeSource_Radious 10.0
#define TubeSource_NumberOfSides 30

#define ConeHeight 50.0
#define ConeBase_Radious 20.0
#define ConeSource_NumberOfSides 30

enum ConePlace{OnPoint1, OnPoint2};

class misNavigatorGuiderRepresentation :
	public misSurfaceRepresentation
{
private:
	/*misNavigatorGuider* m_LineActor;
	misNavigatorGuider* m_ConeActor;*/

	misNavigatorGuider* m_StlActor;

	vtkTextActor*		m_txtActorVal;
	vtkTextActor*		m_txtActorValDescription;

	////To draw body of an arrow
	//vtkLineSource*		m_LineSource;
	////To fatify the above line 
	//vtkTubeFilter*		m_TubeSource;
	////To represent the director(apex) of the arrow 
	ConePlace			m_ConePlace;

public:
	misNavigatorGuiderRepresentation(string name);
	~misNavigatorGuiderRepresentation(void);

	igstkStandardClassBasicTraitsMacro( misNavigatorGuiderRepresentation, misSurfaceRepresentation ) 

	//Makes a new object. NOTICE that the string argument called 'name', in this class, determines the place where the widget places
	static Pointer New(string name);

	void SetLinePoints(double Pos1[3], double Pos2[3]);
	/*void SetConePoint(double Pos1[3]);*/
	void SetConePlace(ConePlace place);
	void SetGuidedNote(double angle);
	void SetGuidedNotePos(double x, double y );
	void SetGuidedNoteDescription(string description);
	void SetGuidedNoteDescriptionPos( double x, double y );

#pragma  region AddedByMehran

	//double FindAngleBetween2vectors(double [] Vec1, double [] Vec2);

#pragma endregion
};

