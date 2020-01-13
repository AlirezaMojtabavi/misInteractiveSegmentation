#include "stdafx.h"
#include "misIntractionCameraStyle.h"

misIntractionCameraStyle::misIntractionCameraStyle(void)
{
	this->m_stepsNumber=STEPNUMBER  ;
	m_ScaleCameraPosition = 3.5;
}

misIntractionCameraStyle::~misIntractionCameraStyle(void)
{
}

void misIntractionCameraStyle::SetRender(vtkRenderer *ren)
{
	this->render=ren;
}
//--------  Line Movement ------------------


CameraLineListTypedef misIntractionCameraStyle::ComputeCameraLinerPointList(double start[3], double end[3])
{

	misPositionStr cameraStr;
	CameraLineListTypedef  cameraLineList;
	//--------------
	double XPart,YPart,ZPart;
	double Xdistance,Ydistance,Zdistance;
	//------
	Xdistance=(end[0])-(start[0]);
	XPart=Xdistance/m_stepsNumber;
	//------
	Ydistance=(end[1])-(start[1]);
	YPart=Ydistance/m_stepsNumber;
	//------
	Zdistance=(end[2])-(start[2]);
	ZPart=Zdistance/m_stepsNumber;
	//----------------
	double X=start[0],Y=start[1],Z=start[2];
	for (int i=0;i<m_stepsNumber;i++)
	{
		X+=XPart;
		Y+=YPart;
		Z+=ZPart;
		cameraStr.XPoint=X;
		cameraStr.YPoint=Y;
		cameraStr.ZPoint=Z;
		cameraLineList.push_back(cameraStr);
	}
	return cameraLineList;
}
//*********
void misIntractionCameraStyle::CameraLineMove()
{

 
	CameraLineListTypedef viewUpList;
	double startViewUp[3];
	this->render->GetActiveCamera()->GetViewUp(startViewUp);
	viewUpList=ComputeCameraLinerPointList(startViewUp,this->m_endViewUp);
	CameraLineListTypedef::iterator view_iter;
	//----------------------
	CameraLineListTypedef LineList;
	LineList=ComputeCameraLinerPointList(m_StartPoint,m_endPoint);
	CameraLineListTypedef::iterator Line_iter;
	//-----------------
	for(Line_iter=LineList.begin(),view_iter=viewUpList.begin();Line_iter!=LineList.end(),view_iter!=viewUpList.end();Line_iter++,view_iter++)
	{
		misPositionStr viewStr;
		viewStr=*(view_iter);
		misPositionStr  CameraLineStr;
		CameraLineStr=*(Line_iter);
		this->render->GetActiveCamera()->SetClippingRange(-1000,100);
		this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint);
		this->render->GetActiveCamera()->SetViewUp(viewStr.XPoint,viewStr.YPoint,viewStr.ZPoint);
		this->render->GetActiveCamera()->SetPosition((CameraLineStr.XPoint)+m_focalPoint[0],(CameraLineStr.YPoint)+m_focalPoint[1],(CameraLineStr.ZPoint)+m_focalPoint[2]);
		this->render->GetRenderWindow()->Render();
	}
}
//--------- End Line Movement ----------------
//--------- Camera Circle Movement -----------

//compute m_radius
void misIntractionCameraStyle::accountantRadius(double *currentPoint)
{
	this->m_radius=sqrt(pow(currentPoint[0],2)+pow(currentPoint[1],2)+pow(currentPoint[2],2));
}
//located next vector location
PositionListTypedef misIntractionCameraStyle::NextPointLocateList()
{
	misPositionStr  PositionStr;
	PositionListTypedef  PositionList;
	for (int i=0;i<this->m_stepsNumber;i++)
	{
		double nextPoint[3]={0,0,0};
		nextPoint[0]=(this->m_radius)*(cos(this->m_tempPhi))*(sin (this->m_tempTheta));
		nextPoint[1]=(this->m_radius)*(sin(this->m_tempPhi))*(sin (this->m_tempTheta));
		nextPoint[2]=(this->m_radius)*(cos(this->m_tempTheta));
		//--------------------
		PositionStr.XPoint=nextPoint[0];
		PositionStr.YPoint=nextPoint[1];
		PositionStr.ZPoint=nextPoint[2];
		PositionList.push_back(PositionStr);
		//--------------------
		this->m_tempPhi += this->m_phiPart;
		this->m_tempTheta += this->m_thetaPart;
	}
	return PositionList;
}
//get vector
void misIntractionCameraStyle::GetCurrentPoint()
{
	this->render->GetActiveCamera()->GetPosition(this->m_StartPoint);
	this->accountantRadius(this->m_StartPoint);
}
//--------- End Camera Circle Movement -----------

//fly camera 
void misIntractionCameraStyle::FlyINCamera()
{

	// get current point and compute m_radius
	GetCurrentPoint();
	// compute phi and theta angle
	misInteractionMathematicalAccount * MathematicalAccount=new misInteractionMathematicalAccount();
	//-----------------
	misAngle pointAngleStr;
	pointAngleStr=MathematicalAccount->accountantPhiAndTheta(this->m_StartPoint,this->m_endPoint);
	SetPhiTheta(pointAngleStr);
	// compute list of position
	PositionListTypedef cameraPositionList;
	cameraPositionList=NextPointLocateList();
	//--------------------------------
	double startViewUp[3];
	this->render->GetActiveCamera()->GetViewUp(startViewUp);
	accountantRadius(startViewUp);
	misAngle viewAngleStr;
	viewAngleStr=MathematicalAccount->accountantPhiAndTheta(startViewUp,this->m_endViewUp);
	SetPhiTheta(viewAngleStr);
	PositionListTypedef viewUpList;
	viewUpList=NextPointLocateList();
	//----------------------------------
	PositionListTypedef::iterator camera_iter,viewUp_iter;
	double v[3];
	misPositionStr vstr;
	PositionListTypedef vlist;
	for(camera_iter=cameraPositionList.begin(),viewUp_iter=viewUpList.begin() ; camera_iter!=cameraPositionList.end() , viewUp_iter!=viewUpList.end() ; camera_iter++,viewUp_iter++)
	{
		this->render->GetActiveCamera()->GetViewUp(v);
		vstr.XPoint=v[0];
		vstr.YPoint=v[1];
		vstr.ZPoint=v[2];
		vlist.push_back(vstr);


		misPositionStr cameraPos,viewPos;
		cameraPos=*(camera_iter);
		viewPos=*(viewUp_iter);
		//---------------------
		//vtkLineSource *pline =vtkLineSource::New();
		//pline->SetPoint1(0,0,0);
		//pline->SetPoint2(cameraPos.XPoint,cameraPos.YPoint,cameraPos.ZPoint);
		//vtkActor *lineActor=vtkActor::New();
		//vtkPolyDataMapper *mapper=vtkPolyDataMapper::New();
		//mapper->SetInput(pline->GetOutput());
		//lineActor->SetMapper(mapper);
		//render->AddActor(lineActor);
		//---------------------
		this->render->GetActiveCamera()->SetClippingRange(-10000,10000);
		this->render->GetActiveCamera()->SetFocalPoint(this->m_focalPoint);
		this->render->GetActiveCamera()->SetViewUp(viewPos.XPoint,viewPos.YPoint,viewPos.ZPoint);
		this->render->GetActiveCamera()->SetPosition(cameraPos.XPoint+m_focalPoint[0],cameraPos.YPoint+m_focalPoint[1],cameraPos.ZPoint+m_focalPoint[2]);

		this->render->GetRenderWindow()->Render();
	}

	this->render->GetActiveCamera()->OrthogonalizeViewUp();

}
//----------------------------------------------------------------------------
//----------- Camera MoveMent -------------------
//void misIntractionCameraStyle::CameraMove(misMoveKind MoveKind)
//{
//   switch (MoveKind)
//   {	
//		case Circle:
//			
//			break;
//		case Line:
//			CameraLineMove();
//			break;
//   }
//}
//----------------------------------------------------------------------------

//-----------------------------------------------
// Rotate the camera about the view up vector centered at the focal point.
void misIntractionCameraStyle::Azimuth(double angle)
{
	double newPosition[3];
	double *fp = this->render->GetActiveCamera()->GetFocalPoint();
	vtkPerspectiveTransform *Transform=vtkPerspectiveTransform::New();

	Transform->Identity();

	// translate the focal point to the origin,
	// rotate about view up,
	// translate back again

	double view[3];
	this->render->GetActiveCamera()->GetViewUp(view);
	Transform->Translate(+fp[0],+fp[1],+fp[2]);
	Transform->RotateWXYZ(angle,view);
	Transform->Translate(-fp[0],-fp[1],-fp[2]);

	double camerapos[3];
	this->render->GetActiveCamera()->GetPosition(camerapos);
	// apply the transform to the position
	Transform->TransformPoint(camerapos,newPosition);
	this->render->GetActiveCamera()->SetPosition(newPosition);
	this->render->GetActiveCamera()->OrthogonalizeViewUp();
}
//-------------------------------------------------
// Rotate the camera about the cross product of the negative of the
// direction of projection and the view up vector centered on the focal point.
void  misIntractionCameraStyle::Elevation(double angle)
{
	double newPosition[3];
	double *fp = this->render->GetActiveCamera()->GetFocalPoint();
	vtkPerspectiveTransform * Transform=vtkPerspectiveTransform::New();
	Transform->Identity();

	vtkTransform * ViewTransform = vtkTransform::New();

	// translate the focal point to the origin,
	// rotate about axis,
	// translate back again
	double view[3],outsideProduct[3],axis[3],position[3];
	this->render->GetActiveCamera()->GetViewUp(view);
	this->render->GetActiveCamera()->GetPosition(position);

	axis[0]=(position[0]-fp[0]);
	axis[1]=(position[1]-fp[1]);
	axis[2]=(position[2]-fp[2]);

	outsideProduct[0]=view[1]*axis[2]-view[2]*axis[1];
	outsideProduct[1]=view[2]*axis[0]-view[0]*axis[2];
	outsideProduct[2]=view[0]*axis[1]-view[1]*axis[0];

	Transform->Translate(+fp[0],+fp[1],+fp[2]);
	Transform->RotateWXYZ(-angle,outsideProduct);
	Transform->Translate(-fp[0],-fp[1],-fp[2]);

	double camerapos[3];
	this->render->GetActiveCamera()->GetPosition(camerapos);
	// now transform position
	Transform->TransformPoint(camerapos,newPosition);
	this->render->GetActiveCamera()->SetPosition(newPosition);
	this->render->GetActiveCamera()->OrthogonalizeViewUp();
}
////----------------------------------
//// set camera point in to xPoint
//void misIntractionCameraStyle::SupriorView()
//{
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,1,0);
//	double zDirectionWidth=(pBounding[5]-pBounding[4]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]-zDirectionWidth * this->m_ScaleCameraPosition);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//
//
//
//}
////-------------------------------------
//// set camera point in to yPoint
//void misIntractionCameraStyle::InferiorView()
//{
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,1,0);
//	double zDirectionWidth=(pBounding[5]-pBounding[4]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]+zDirectionWidth * this->m_ScaleCameraPosition);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//}
////--------------------------------------
//// set camera point in to ZPoint  
//void misIntractionCameraStyle::AnteriorView()
//{
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,0,-1);
//	double yDirectionWidth=(pBounding[3]-pBounding[2]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0] ,m_focalPoint[1]+yDirectionWidth * this->m_ScaleCameraPosition,m_focalPoint[2]);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//	//this->render->GetActiveCamera()->OrthogonalizeViewUp();
//	
//}//----------------------------------
//void misIntractionCameraStyle::PosteriorView()
//{
//
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,0,-1);
//	double yDirectionWidth=(pBounding[3]-pBounding[2]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0] ,m_focalPoint[1]-yDirectionWidth * this->m_ScaleCameraPosition,m_focalPoint[2]);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//	//this->render->GetActiveCamera()->OrthogonalizeViewUp();
//
//
//}//----------------------------------
//// set camera point in to xPoint
//void misIntractionCameraStyle::LleftView()
//{
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,0,-1);
//	double xDirectionWidth=(pBounding[1]-pBounding[0]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0]+xDirectionWidth * this->m_ScaleCameraPosition,m_focalPoint[1],m_focalPoint[2]);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//
//
//}
////-------------------------------------
//// set camera point in to yPoint
//void misIntractionCameraStyle::RRightView()
//{
//	double*  pBounding=this->render->ComputeVisiblePropBounds();
//	m_focalPoint[0]=(pBounding[1]-pBounding[0])*0.5;
//	m_focalPoint[1]=(pBounding[3]-pBounding[2])*0.5;
//	m_focalPoint[2]=(pBounding[5]-pBounding[4])*0.5;
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,0,-1);
//	double xDirectionWidth=(pBounding[1]-pBounding[0]);
//	this->render->GetActiveCamera()->SetPosition(m_focalPoint[0]-xDirectionWidth * this->m_ScaleCameraPosition ,m_focalPoint[1],m_focalPoint[2]);
//	this->render->ResetCameraClippingRange();
//	this->render->GetRenderWindow()->Render();
//
//	 
//}
////--------------------------------------
//// set camera point in to ZPoint
//void misIntractionCameraStyle::CameraZPoint2()
//{
//	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint[0],m_focalPoint[1],m_focalPoint[2]);
//	this->render->GetActiveCamera()->SetViewUp(0,1,0);
//	this->render->GetActiveCamera()->SetPosition(0,0,-m_cameraPosition[2]);
//	this->render->GetActiveCamera()->SetClippingRange(-20000,20000);
//	this->render->GetRenderWindow()->Render();
//	//this->render->GetActiveCamera()->OrthogonalizeViewUp();
//}
//------------------------------------------------------------
//set camera position
void misIntractionCameraStyle::SetCameraPosition(double* position)
{
	this->m_cameraPosition[0]=position[0];
	this->m_cameraPosition[1]=position[1];
	this->m_cameraPosition[2]=position[2];
}
//get camera position
double misIntractionCameraStyle::GetCameraPosition()
{
	return *m_cameraPosition;
}

//----------------------------------------------------------
//set focal point
void  misIntractionCameraStyle::SetFocalPoint(double *focal)
{
	this->m_focalPoint[0]=focal[0];
	this->m_focalPoint[1]=focal[1];
	this->m_focalPoint[2]=focal[2];
}
//get focal point
double  misIntractionCameraStyle::GetFocalPoint()
{
	return * m_focalPoint;
}

//void misIntractionCameraStyle::accountantPhiAndTheta( double startPoint[3],double m_endPoint[3] )
//{
//		double theta1,theta2;
//		double phi1,phi2;
//		double phiDistance2vector;
//		double thetaDistance2Vector;
//
//	
//		// angle between vector and z axis
//		theta1=acos(startPoint[2]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2)+pow(startPoint[2],2))));
//		theta2=acos(m_endPoint[2]/(sqrt(pow(m_endPoint[0],2)+pow(m_endPoint[1],2)+pow(m_endPoint[2],2))));
//
//		//if (startPoint[0]>=0)
//		//{
//		//	phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))));
//		//}
//		//else if (startPoint[0]<0)
//		//{
//		//	phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))))+vtkMath::Pi();
//		//}
//		////---------------------		
//		//if (m_endPoint[0]>=0)
//		//{
//		//	phi2=asin(m_endPoint[1]/(sqrt(pow(m_endPoint[0],2)+pow(m_endPoint[1],2))));
//		//}
//		//else if (m_endPoint[0]<0)
//		//{
//		//	phi2=asin(m_endPoint[1]/(sqrt(pow(m_endPoint[0],2)+pow(m_endPoint[1],2))))+ vtkMath::Pi();
//		//}
//		//phi1=asin(startPoint[1]/(sqrt(pow(startPoint[0],2)+pow(startPoint[1],2))));
//		//phi2=asin(m_endPoint[1]/(sqrt(pow(m_endPoint[0],2)+pow(m_endPoint[1],2))));
//
//
//		if (startPoint[0]==0)
//		{
//		   if(startPoint[1]>0)	
//		   {
//			   phi1=vtkMath::Pi()/2;
//		   }
//		   else
//		   {
//			   phi1=-vtkMath::Pi()/2;
//		   }
//		}
//		else if (startPoint[0]<0)
//		{
//			if (startPoint[1]>=0)
//			{
//				phi1=atan(startPoint[1]/startPoint[0])+ vtkMath::Pi();
//
//			}
//			else if(startPoint[1]<0)
//			{
//				phi1=atan(startPoint[1]/startPoint[0])- vtkMath::Pi();
//
//			}
//		}
//		else if (startPoint[0]>0)
//		{
//			phi1=atan(startPoint[1]/startPoint[0]);
//		}
//		//*----------------------------	
//		if (m_endPoint[0]==0)
//		{
//			if(m_endPoint[1]>0)	
//			{
//				phi2=vtkMath::Pi()/2;
//			}
//			else
//			{
//				phi2=-vtkMath::Pi()/2;
//			}
//		}
//		else if (m_endPoint[0]<0)
//		{
//			if (m_endPoint[1]>=0)
//			{
//				phi2=atan(m_endPoint[1]/m_endPoint[0])+ vtkMath::Pi();
//			}
//			else if(m_endPoint[1]<0)
//			{
//				phi2=atan(m_endPoint[1]/m_endPoint[0])- vtkMath::Pi();
//			}
//		}
//		else if(m_endPoint[0]>0)
//		{
//			phi2=atan(m_endPoint[1]/m_endPoint[0]);
//		}
//
//		phiDistance2vector=(phi2-phi1);
//		thetaDistance2Vector=(theta2-theta1);
//	
//		m_phiPart=phiDistance2vector/this->m_stepsNumber;
//		m_thetaPart=thetaDistance2Vector/this->m_stepsNumber;
//
//		m_tempPhi=phi1;
//		m_tempTheta=theta1;
//}

void misIntractionCameraStyle::PageUPCamera()
{
	double position[3]={0,0,0};
	double  m_focalPoint[3];
	this->render->GetActiveCamera()->GetPosition(position);
	this->render->GetActiveCamera()->GetFocalPoint(m_focalPoint);
	m_focalPoint[1]--;
	this->render->GetActiveCamera()->SetFocalPoint(m_focalPoint);
	position[1]--;
	this->render->GetActiveCamera()->SetPosition(position);

}

void misIntractionCameraStyle::PageDownCamera()
{
	double position[3]={0,0,0};
	double focalpoint[3];
	this->render->GetActiveCamera()->GetFocalPoint(focalpoint);
	this->render->GetActiveCamera()->GetPosition(position);
	focalpoint[1]++;
	this->render->GetActiveCamera()->SetFocalPoint(focalpoint);
	position[1]++;
	this->render->GetActiveCamera()->SetPosition(position);

}

void misIntractionCameraStyle::UPCamera()
{
	double position[3]={0,0,0};
	double focalpoint[3];
	this->render->GetActiveCamera()->GetFocalPoint(focalpoint);
	this->render->GetActiveCamera()->GetPosition(position);
	focalpoint[2]++;
	this->render->GetActiveCamera()->SetFocalPoint(focalpoint);
	position[2]++;
	this->render->GetActiveCamera()->SetPosition(position);

}

void misIntractionCameraStyle::DownCamera()
{
	double position[3]={0,0,0};
	double focalpoint[3];
	this->render->GetActiveCamera()->GetFocalPoint(focalpoint);
	this->render->GetActiveCamera()->GetPosition(position);
	focalpoint[2]--;
	position[2]--;
	this->render->GetActiveCamera()->SetPosition(position);
	this->render->GetActiveCamera()->SetFocalPoint(focalpoint);

}

void misIntractionCameraStyle::RightCamera()
{
	double position[3]={0,0,0};
	double focalpoint[3]={0,0,0};
	this->render->GetActiveCamera()->GetFocalPoint(focalpoint);
	this->render->GetActiveCamera()->GetPosition(position);
	focalpoint[0]--;
	position[0]--;
	this->render->GetActiveCamera()->SetPosition(position);
	this->render->GetActiveCamera()->SetFocalPoint(focalpoint);

}

void misIntractionCameraStyle::LeftCamera()
{
	double position[3]={0,0,0};
	double focalpoint[3]={0,0,0};
	this->render->GetActiveCamera()->GetFocalPoint(focalpoint);
	this->render->GetActiveCamera()->GetPosition(position);
	focalpoint[0]++;
	position[0]++;
	this->render->GetActiveCamera()->SetPosition(position);
	this->render->GetActiveCamera()->SetFocalPoint(focalpoint);

}

void misIntractionCameraStyle::SetPhiTheta( misAngle  angleStr)
{
	double phiDistance2vector=(angleStr.phi2-angleStr.phi1);
	double thetaDistance2Vector=(angleStr.thetha2-angleStr.theta1);

	this->m_phiPart=phiDistance2vector/this->m_stepsNumber;
	this->m_thetaPart=thetaDistance2Vector/this->m_stepsNumber;

	this->m_tempPhi=angleStr.phi1;
	this->m_tempTheta=angleStr.theta1;
}

void misIntractionCameraStyle::SetScaleCameraPosition( double  scaleCameraPosition)
{
 
	if (scaleCameraPosition > 10)
		scaleCameraPosition = 10;

	if (scaleCameraPosition < 2)
		scaleCameraPosition = 2;

	this->m_ScaleCameraPosition = scaleCameraPosition;
}

double misIntractionCameraStyle::GetScaleCameraPosition( void )
{
  return this->m_ScaleCameraPosition;
}
//--------------------------------------------------------------

