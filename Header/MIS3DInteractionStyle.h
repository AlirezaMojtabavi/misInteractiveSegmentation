#ifndef __MIS3DInteractionStyle_
#define __MIS3DInteractionStyle_

#pragma once

#include "misInteractionMathematicalAccount.h"
#include "misInteractionMathematicalAccount.h"
#include "misInteractionObjectStyle.h"
#include "misIntractionCameraStyle.h"
#include "misSelectionElement.h"

#define  misMouseMoveEvent  1
#define  noEvent         2
#define  DollyEvent		 3
#define  PanEvent_3d	 4
#define  interctionEvent	 vtkCommand::UserEvent+3000

struct actorProperty
{
	double *center;
	double distance;
};
typedef std::list<actorProperty>    distanceTypeDef;

// MIS3DInteractionStyle allows the user to interactively
// manipulate (rotate, pan, etc.) the camera, the viewpoint of the scene.  In
// trackball interaction, the magnitude of the mouse motion is proportional
// to the camera motion associated with a particular mouse binding. For
// example, small left-button motions cause small changes in the rotation of
// the camera around its focal point. For a 3-button mouse, the left button
// is for rotation, the right button for zooming, the middle button for
// panning, and ctrl + left button for spinning.  (With fewer mouse buttons,
// ctrl + shift + left button is for zooming, and shift + left button is for
// panning.)

class   MIS3DInteractionStyle: public vtkInteractorStyleTrackballCamera
{
	
public:

	MIS3DInteractionStyle(vtkPicker* picker);
	~MIS3DInteractionStyle(void);
	static MIS3DInteractionStyle *New(vtkPicker* picker);
	void SetInitialize();
	void SetFocalPoint(double *);
	double GetFocalPoint();
	void SetCameraPosition(double *);
	double GetCameraPosition();
	virtual void OnKeyDown();
	virtual void OnMouseMove();
	virtual void OnRightButtonDown();
	virtual void Spin();
	virtual void OnLeftButtonDown();
	virtual void OnLeftButtonUp();
	vtkPicker* GetPointPicker() const;
	void SetCameraObject();
	virtual void Dolly(double factor);
	virtual void Dolly();
	void SetNavigationMode();
	void  eventLUTable();
	std::vector<misSelectionElement>   GetSelctionElements( );
	int GetState() const;
	void SetState(int val);
private:
	misIntractionCameraStyle *IntractionCamera;
	misInteractionMathematicalAccount  m_InteractionMath;
	double								m_CameraPosition[3];
	double								m_FocalPoint[3];
	std::vector<misSelectionElement>	m_elements;
	vtkPicker*							m_PointPicker;
	bool								m_InitializeFlag;
	int									m_State;

	double								m_SpinFactor;
	int									m_MouseEvent;
};

#endif
