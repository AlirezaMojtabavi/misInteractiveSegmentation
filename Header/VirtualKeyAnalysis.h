#pragma once
#include "misTimePassingForAction.h"
#include "misPlate.h"
#include "vtkTransform.h"
#include "VirtualKeyStruct.h"
#include "misHexFaceObject.h"

class VirtualKeyAnalysis: public misTimePassingForAction
{
public:
	static VirtualKeyAnalysis* New(){return new VirtualKeyAnalysis();}
	~VirtualKeyAnalysis(void);
	
	void SetPosition(double position[3]);

	double				GetActionValue(void); 
	void				GetActionValue(VirtualKeyProprties& virtualKeyPro); 
	int					GetRegionID();
	bool                GetVirtualKeyWindowStatus(void);
	
	//must be called in the inherited class constructor
	void UpdateAllSetting(misToolFixationPropertiesStr str);
	
	void SetTransformMatrix(vtkMatrix4x4* TransformMatrix);

private:
	VirtualKeyAnalysis(void);
	VirtualKeyProprties CalcActionValue();

private:
	int				  m_LastRegionIDDetected;
	misPlate		  m_Plate;
	double			  m_Position[3];
	vtkTransform*	  m_TransformMatrix;
	bool			  m_IsTransformSet;
	misHexFaceObject  m_VirtualKeyActiveRegion;
};

