#include "stdafx.h"

#include "MIS3DInteractionStyle.h"
#include "misInteractionObjectStyle.h"
 
using namespace std;

MIS3DInteractionStyle::MIS3DInteractionStyle(vtkPicker* picker)
	: m_MouseEvent(noEvent), m_State(noEvent), m_InitializeFlag(true), m_SpinFactor(0.5),
	 IntractionCamera(NULL),
	m_PointPicker(picker)
{
	AutoAdjustCameraClippingRange = false;
}

MIS3DInteractionStyle::~MIS3DInteractionStyle(void)
{
	if (m_PointPicker)
		m_PointPicker->Delete();
	m_PointPicker=0;

}

void MIS3DInteractionStyle::SetInitialize()
{
	//-------------
	this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], 
		this->Interactor->GetEventPosition()[1]);
	if (this->CurrentRenderer == NULL)
	{
		return;
	}
	this->CurrentRenderer=this->GetCurrentRenderer();
	//-------------
	double bounds[6];
	this->CurrentRenderer->ComputeVisiblePropBounds(bounds);
	double Xmin=0,Xmax=0,Ymin=0,Ymax=0,Zmin=0,Zmax=0 ;
	Xmin=bounds[0];
	Xmax=bounds[1];
	Ymin=bounds[2];
	Ymax=bounds[3];   
	Zmin=bounds[4];
	Zmax=bounds[5];
	//*************
	double focalPoint[3];
	focalPoint[0]=(Xmax+Xmin)/2;
	focalPoint[1]=(Ymax+Ymin)/2;
	focalPoint[2]=(Zmax+Zmin)/2;
	this->SetFocalPoint(focalPoint);
	//**************
	double cameraPosition[3];
	cameraPosition[0]=(Xmax*13);
	cameraPosition[1]=(Ymax*11);
	cameraPosition[2]=(Zmax*4);
	this->SetCameraPosition(cameraPosition);

	this->SetCameraObject();
}

void MIS3DInteractionStyle::SetFocalPoint( double *focal )
{
	this->m_FocalPoint[0]=focal[0];
	this->m_FocalPoint[1]=focal[1];
	this->m_FocalPoint[2]=focal[2];
}

void MIS3DInteractionStyle::SetCameraPosition( double * position)
{
	this->m_CameraPosition[0]=position[0];
	this->m_CameraPosition[1]=position[1];
	this->m_CameraPosition[2]=position[2];
}

void MIS3DInteractionStyle::SetCameraObject()
{
	if (!this->Interactor)
		return;
	this->IntractionCamera=new misIntractionCameraStyle();
	IntractionCamera->SetRender(this->CurrentRenderer);
	IntractionCamera->SetCameraPosition(this->m_CameraPosition);
	IntractionCamera->SetFocalPoint(this->m_FocalPoint);
}

void MIS3DInteractionStyle::SetNavigationMode()
{
	double eye[3];
	int x;
	int y;
	this->Interactor->GetEventPosition(x,y);
	double position[3];
	m_PointPicker->Pick(x,y,0,this->CurrentRenderer);
	vtkPoints* pos=vtkPoints::New();
	pos=m_PointPicker->GetPickedPositions();
	vtkIdType num = pos->GetNumberOfPoints();
	vtkIdType index=0;
	double min = 0;
	int i=0;
	if (num==0)
		return;
	while(i<num)
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(eye);
		pos->GetPoint(i,position);
		double distance =vtkMath::Distance2BetweenPoints(eye,position);
		if (i == 0)
			min = distance;
		if (distance < min)
		{
			min = distance;
			index = i;
		}
		i++;
	}
	double  newPos[3];
	pos->GetPoint(index,newPos);

	//---------------------
	vtkProp3DCollection * prop3Dcollect=m_PointPicker->GetProp3Ds(); 
	prop3Dcollect->InitTraversal();
	vtkProp3D * prop;
	int numberOfProp=prop3Dcollect->GetNumberOfItems();
	int propIndex=0;
	min=0;
	int counter=0;
	while(counter<numberOfProp)
	{
		prop=prop3Dcollect->GetNextProp3D();
		double actorPos[3]; 
		prop->GetPosition(actorPos);
		this->CurrentRenderer->GetActiveCamera()->GetPosition(eye);
		double distance =vtkMath::Distance2BetweenPoints(eye,actorPos);
		if (counter==0)
			min=distance;
		if (distance<min)
		{
			min = distance;
			propIndex=counter;
		}
		counter++;
	}
	//-----------
	vtkProp3D * baseActor=NULL;
	vtkProp3DCollection * prop3Dcollect2=m_PointPicker->GetProp3Ds();
	prop3Dcollect2->InitTraversal();
	for (int j=0; j<=propIndex ; j++)
	{
		baseActor=prop3Dcollect2->GetNextProp3D();
	}
	//-------------

	if (numberOfProp)
	{
		double *center= baseActor->GetCenter();

		double newCameraPos[3];
		newCameraPos[0]=center[0] + (1.7*(newPos[0]- center[0]));
		newCameraPos[1]=center[1] + (1.7*(newPos[1]- center[1]));
		newCameraPos[2]=center[2] + (1.7*(newPos[2]- center[2]));

		//=================
		this->CurrentRenderer->GetActiveCamera()->SetPosition(newCameraPos);
		this->CurrentRenderer->GetActiveCamera()->OrthogonalizeViewUp();

		this->CurrentRenderer->Render();
	}

}





vtkPicker* MIS3DInteractionStyle::GetPointPicker() const
{
	return m_PointPicker;
}

void MIS3DInteractionStyle::OnKeyDown()
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
	//------------------------
	vtkInteractorStyleTrackballCamera::OnKeyDown();
	char * strControlKey=this->Interactor->GetKeySym();
	if(strControlKey[0]=='1') 
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(IntractionCamera->m_StartPoint);
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=-IntractionCamera->m_radius;
		IntractionCamera->m_endPoint[1]=0;
		IntractionCamera->m_endPoint[2]=0;
		//----------------------------
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=1;
		IntractionCamera->m_endViewUp[2]=0;

		IntractionCamera->CameraLineMove();

	}else if(strControlKey[0]=='3') 
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(IntractionCamera->m_StartPoint);
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=0;
		IntractionCamera->m_endPoint[1]=IntractionCamera->m_radius;
		IntractionCamera->m_endPoint[2]=0;
		//----------------------------
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=0;
		IntractionCamera->m_endViewUp[2]=-1;
		IntractionCamera->CameraLineMove();

	}else if(strControlKey[0]=='7') 
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(IntractionCamera->m_StartPoint);
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=0;
		IntractionCamera->m_endPoint[1]=0;
		IntractionCamera->m_endPoint[2]=IntractionCamera->m_radius;
		//----------------------------
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=1;
		IntractionCamera->m_endViewUp[2]=0;
		IntractionCamera->CameraLineMove();
	}

	//**************************
	else if(strControlKey[0]=='a') 
	{
		//IntractionCamera->CameraXPoint1();
		//interactionObject->MoveObjectX(90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();

	}else if(strControlKey[0]=='b') 
	{
		//IntractionCamera->CameraXPoint2();
		//interactionObject->MoveObjectX(-90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();

	}else if(strControlKey[0]=='c') 
	{
		//		IntractionCamera->CameraYPoint1();
		//interactionObject->MoveObjectY(90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();

	}else if(strControlKey[0]=='d') 
	{
		//IntractionCamera->CameraYPoint2();
		//interactionObject->MoveObjectY(-90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();

	}else if(strControlKey[0]=='e') 
	{
		//		IntractionCamera->CameraZPoint1();
		//interactionObject->MoveObjectZ(90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();

	}else if(strControlKey[0]=='f') 
	{
		//IntractionCamera->CameraZPoint2();
		//interactionObject->MoveObjectZ(-90);
		//vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
		//matrix=interactionObject->GetFinalTransformMatrix();
	}
	//**************************
	else if(strControlKey[0]=='6')
	{
		IntractionCamera->Azimuth(-90);
		this->Interactor->Render();

	} else if(strControlKey[0]=='4')
	{
		IntractionCamera->Azimuth(90);
		this->Interactor->Render();

	} else if(strControlKey[0]=='2')
	{
		IntractionCamera->Elevation(90);
		this->Interactor->Render();

	} else if(strControlKey[0]=='8')
	{
		IntractionCamera->Elevation(-90);
		this->Interactor->Render();

	} else if(strControlKey[0]=='x')
	{
		//-------------------
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=-IntractionCamera->m_radius;
		IntractionCamera->m_endPoint[1]=0;
		IntractionCamera->m_endPoint[2]=0;
		//---------------------
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=1;
		IntractionCamera->m_endViewUp[2]=0;
		//---------------------
		IntractionCamera->FlyINCamera();
		this->Interactor->GetRenderWindow()->Render();
	}
	else if(strControlKey[0]=='y')
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(IntractionCamera->m_StartPoint);
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=0;
		IntractionCamera->m_endPoint[1]=IntractionCamera->m_radius;
		IntractionCamera->m_endPoint[2]=0;
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=0;
		IntractionCamera->m_endViewUp[2]=-1;
		IntractionCamera->FlyINCamera();
	}			
	else if(strControlKey[0]=='z')
	{
		this->CurrentRenderer->GetActiveCamera()->GetPosition(IntractionCamera->m_StartPoint);
		IntractionCamera->accountantRadius(IntractionCamera->m_StartPoint);
		IntractionCamera->m_endPoint[0]=0;
		IntractionCamera->m_endPoint[1]=0;
		IntractionCamera->m_endPoint[2]=IntractionCamera->m_radius;
		IntractionCamera->m_endViewUp[0]=0;
		IntractionCamera->m_endViewUp[1]=1;
		IntractionCamera->m_endViewUp[2]=0;
		IntractionCamera->FlyINCamera();

	}
	/*else 	if (strControlKey[0] =='P' )
	{
	IntractionCamera->PageUPCamera();		
	this->Interactor->Render();

	}else if (strControlKey[0] == 'N')
	{
	IntractionCamera->PageDownCamera();
	this->Interactor->Render();

	}else if (strControlKey[0] == 'U')
	{
	IntractionCamera->UPCamera();
	this->Interactor->Render();

	}else if (strControlKey[0] == 'D')
	{
	IntractionCamera->DownCamera();
	this->Interactor->Render();

	}else if (strControlKey[0] == 'R')
	{
	IntractionCamera->RightCamera();
	this->Interactor->Render();

	}else if (strControlKey[0] == 'L')
	{
	IntractionCamera->LeftCamera();
	this->Interactor->Render();
	}*/

	this->CurrentRenderer->GetRenderWindow()->Render();
}

void MIS3DInteractionStyle::OnLeftButtonDown()
{
	this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], 
		this->Interactor->GetEventPosition()[1]);
	if (this->CurrentRenderer == NULL)
	{
		return;
	}
	switch (this->m_State)
	{
	case DollyEvent:
		this->StartDolly();
		break;
	case PanEvent_3d:
		this->StartPan();
		break;
	}
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void MIS3DInteractionStyle::OnLeftButtonUp()
{
	this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], 
		this->Interactor->GetEventPosition()[1]);
	if (this->CurrentRenderer == NULL)
	{
		return;
	}
	switch (this->State) 
	{
	case VTKIS_DOLLY:
		this->EndDolly();
		break;

	case VTKIS_PAN:
		this->EndPan();
		break;

	case VTKIS_SPIN:
		this->EndSpin();
		break;

	case VTKIS_ROTATE:
		this->EndRotate();
		break;
	}

	// this->m_State=noEvent;

	if ( this->Interactor )
	{
		this->ReleaseFocus();
	}

}

void MIS3DInteractionStyle::OnRightButtonDown()
{
	SetNavigationMode();
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

void MIS3DInteractionStyle::OnMouseMove()
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	}


	vtkInteractorStyleTrackballCamera::OnMouseMove();


}

void MIS3DInteractionStyle::Dolly(double factor)
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 

	if (!this->Interactor)
		return;

	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if (camera->GetParallelProjection())
	{
		camera->SetParallelScale(camera->GetParallelScale() / factor);
	}
	else
	{
		camera->Dolly(factor);

	}

	if (this->Interactor->GetLightFollowCamera()) 
	{
		this->CurrentRenderer->UpdateLightsGeometryToFollowCamera();
	}

}

void MIS3DInteractionStyle::Dolly()
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 

	if (!this->Interactor)
		return;

	vtkRenderWindowInteractor *rwi = this->Interactor;
	double *center = this->CurrentRenderer->GetCenter();
	int dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];
	double dyf = this->MotionFactor * dy / center[1];
	this->Dolly(pow(1.1, dyf));

}

void MIS3DInteractionStyle::Spin()
{

	if ( this->Interactor == NULL )
	{
		return;
	}


	vtkRenderWindowInteractor *rwi = this->Interactor;

	double *center = this->CurrentRenderer->GetCenter();

	double newAngle = 
		vtkMath::DegreesFromRadians( atan2( rwi->GetEventPosition()[1] - center[1],
		rwi->GetEventPosition()[0] - center[0] ) );

	double oldAngle = 
		vtkMath::DegreesFromRadians( atan2( rwi->GetLastEventPosition()[1] - center[1],
		rwi->GetLastEventPosition()[0] - center[0] ) );

	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	double rollingAngle=(newAngle - oldAngle)* m_SpinFactor;
	camera->Roll(rollingAngle);
	camera->OrthogonalizeViewUp();

	rwi->Render();

}

void MIS3DInteractionStyle::eventLUTable()
{
	if (this->m_State== DollyEvent)
	{
		this->m_State=DollyEvent;
	}
}





vector<misSelectionElement> MIS3DInteractionStyle::GetSelctionElements()
{
	return  m_elements;
}

MIS3DInteractionStyle * MIS3DInteractionStyle::New(vtkPicker* picker)
{
	return new MIS3DInteractionStyle(picker);
}

int MIS3DInteractionStyle::GetState() const
{
	return m_State;
}

void MIS3DInteractionStyle::SetState( int val )
{
	m_State = val;
}






