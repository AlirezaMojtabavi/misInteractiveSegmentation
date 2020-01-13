#pragma once

#include "misInteractionMathematicalAccount.h"

//===============================================================================
class  misInteractionObjectStyle: public vtkInteractorStyleTrackballCamera
{
private:
	   vtkActorCollection * m_Model;
	   bool m_InitializeFlag;
	   vtkRenderer* render;
	   vtkMatrix4x4 * FinalTransformMatrix;
	   vtkTransform* FinalTransform;
	   vtkActorCollection * ManActor;

public:

		 static misInteractionObjectStyle* New()
	 {
		 return new misInteractionObjectStyle;
	 }

		 void SetInitialize();
		 virtual void OnKeyDown();
	     void RotateObjectX(double);
		 void RotateObjectY(double);
		 void RotateObjectZ(double);
		 void MoveObjectX(double);
		 void MoveObjectY(double);
		 void MoveObjectZ(double);
		 void SetCameraPositionforObjectRotate();
		 vtkMatrix4x4* GetFinalTransformMatrix();
		 vtkTransform * GetFinalTransform();
		 void SetModel(vtkActorCollection *);
		// void setManActors(vtkActorCollection *);

		 void SetRender(vtkRenderer*);

		 double focalPoint[3];
		 void SetFocalPoint(double *);

		 double cameraPosition[3];
		 void SetCameraPosition(double *);

		//------------------------------
		misInteractionObjectStyle(void);
		~misInteractionObjectStyle(void);
};
