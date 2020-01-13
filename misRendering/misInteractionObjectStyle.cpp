#include "stdafx.h"
#include "misInteractionObjectStyle.h"

misInteractionObjectStyle::misInteractionObjectStyle(void)
{
	m_InitializeFlag=true;
	m_Model=NULL;
}
//-------------------
misInteractionObjectStyle::~misInteractionObjectStyle(void)
{
}
//-------------------
//void misInteractionObjectStyle::setManActors( vtkActorCollection * manActors)
//{
//	this->ManActor=manActors;
//}
void misInteractionObjectStyle::SetRender( vtkRenderer* ren)
{
	this->render=ren;
	//double bounds[6];
	//this->render->ComputeVisiblePropBounds(bounds);
	//vtkAxes *axes = vtkAxes::New();
	//axes->SetOrigin(0, 0, 0);
	//axes->SetScaleFactor(30);
	//vtkTubeFilter *axesTubes = vtkTubeFilter::New();
	//axesTubes->SetInputConnection(axes->GetOutputPort());
	//axesTubes->SetRadius(0.5);
	//axesTubes->SetNumberOfSides(6);
	//vtkPolyDataMapper *axesMapper = vtkPolyDataMapper::New();
	//axesMapper->SetInputConnection(axesTubes->GetOutputPort());
	//vtkActor *axesActor = vtkActor::New();
	//axesActor->SetMapper(axesMapper);
	//this->render->AddActor(axesActor);
}
void misInteractionObjectStyle::SetFocalPoint( double * focal )
{
	this->focalPoint[0]=focal[0];
	this->focalPoint[1]=focal[1];
	this->focalPoint[2]=focal[2];
}

void misInteractionObjectStyle::SetCameraPosition( double * position)
{
	this->cameraPosition[0]=position[0];
	this->cameraPosition[1]=position[1];
	this->cameraPosition[2]=position[2];
}
//-------------------
void misInteractionObjectStyle::SetCameraPositionforObjectRotate()
{ 
	this->render->GetActiveCamera()->SetFocalPoint(this->focalPoint);
	this->render->GetActiveCamera()->SetPosition(cameraPosition[0]/2,cameraPosition[1],cameraPosition[2]);
}
//-------------------
void misInteractionObjectStyle::RotateObjectX(double angle)
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	//------  Compute Camera Transform Matrix ----------------
	vtkTransform * Transform=vtkTransform::New();
	double position[3];
	if (!m_Model)
	{
		m_Model=this->render->GetActors();
	}
	//int number=actors->GetNumberOfItems();
	vtkActor* actor1=vtkActor::New();
	m_Model->InitTraversal();
	vtkMatrix4x4 * lastMatrix;
	//****************
	while(actor1=m_Model->GetNextActor())  
	{ 
		actor1->GetPosition(position);
		//----------------
		lastMatrix=vtkMatrix4x4::New();
		lastMatrix=actor1->GetUserMatrix();
		//---------------
		if(lastMatrix)
			Transform->SetMatrix(lastMatrix);
		Transform->Translate(-position[0],-position[1],-position[2]);
		Transform->RotateX(angle);
		Transform->Translate(+position[0],+position[1],+position[2]);
		//----------------
		vtkMatrix4x4* matrix= Transform->GetMatrix();
		//_ASSERT(matrix->Element[0][0]==1.0);
		//_ASSERT(matrix->Element[1][1]==1.0);
		//_ASSERT(matrix->Element[2][2]==1.0);
		//_ASSERT(matrix->Element[3][3]==1.0);

		actor1->SetUserTransform(Transform);
	}
	this->FinalTransformMatrix=Transform->GetMatrix();
	this->FinalTransform=Transform;
	this->render->GetRenderWindow()->Render();
}
//-------------------
//rotate object y-axis
void misInteractionObjectStyle::RotateObjectY(double angle)
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	//------  Compute Camera Transform Matrix ----------------a
	vtkTransform * Transform=vtkTransform::New();
	double position[3];
	vtkMatrix4x4 *lastMatrix; 
	if (!m_Model)
	{
		m_Model=this->render->GetActors();
	}
	vtkActor* actor1=vtkActor::New();
	m_Model->InitTraversal();
	while(actor1=m_Model->GetNextActor())  
	{ 
		actor1->GetPosition(position);
		//----------------
		lastMatrix=vtkMatrix4x4::New();
		lastMatrix=actor1->GetUserMatrix();
		//---------------
		if(lastMatrix)
			Transform->SetMatrix(lastMatrix);
		Transform->Translate(-position[0],-position[1],-position[2]);
		Transform->RotateY(angle);
		Transform->Translate(+position[0],+position[1],+position[2]);
		//----------------
		actor1->SetUserTransform(Transform);
	}
	FinalTransformMatrix=Transform->GetMatrix();
	this->FinalTransform=Transform;
	render->GetRenderWindow()->Render();
}
//-------------------
//rotate object z-axis
void misInteractionObjectStyle::RotateObjectZ(double angle)
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	//------  Compute Camera Transform Matrix ----------------a
	vtkTransform * Transform=vtkTransform::New();
	double position[3];
	vtkActorCollection * actor=this->render->GetActors();
	if (!m_Model)
	{
		m_Model=this->render->GetActors();
	}
	vtkActor* actor1=vtkActor::New();
	m_Model->InitTraversal();
	vtkMatrix4x4 * lastMatrix;
	while(actor1=m_Model->GetNextActor())  
	{ 
		actor1->GetPosition(position);
		//----------------
		lastMatrix=vtkMatrix4x4::New();
		lastMatrix=actor1->GetUserMatrix();
		//---------------
		if(lastMatrix)
			Transform->SetMatrix(lastMatrix);
		Transform->Translate(-position[0],-position[1],-position[2]);
		Transform->RotateZ(angle);
		Transform->Translate(+position[0],+position[1],+position[2]);
		//----------------
		actor1->SetUserTransform(Transform);
	}
	FinalTransformMatrix=Transform->GetMatrix();
	this->FinalTransform=Transform;
    render->GetRenderWindow()->Render();
}
//-------------------
void misInteractionObjectStyle::MoveObjectX(double angle)
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	misInteractionMathematicalAccount * InteractionMathematical=new misInteractionMathematicalAccount();
	//---- set camera position --------
	//SetCameraPositionforObjectRotate();
	//----------------------------------
	doubleListTypeDef angleLST;
	angleLST=InteractionMathematical->FastSlowMotion();
	doubleListTypeDef::iterator angle_iter;
	double s=0;
	for(angle_iter=angleLST.begin();angle_iter!=angleLST.end();angle_iter++)
	{
		double angle1= *(angle_iter);
		angle1*=angle;
		RotateObjectX(angle1);
	}
	this->FinalTransformMatrix=InteractionMathematical->RoundTransformElemnt(this->FinalTransformMatrix);
	//this->FinalTransform->SetMatrix(this->FinalTransformMatrix);
}
//-------------------
void misInteractionObjectStyle::MoveObjectY(double angle )
{
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	misInteractionMathematicalAccount * InteractionMathematical=new misInteractionMathematicalAccount();

	//---- set camera position --------
	//SetCameraPositionforObjectRotate();
	//-------------------------------------
	doubleListTypeDef angleLST;
	angleLST=InteractionMathematical->FastSlowMotion();
	doubleListTypeDef::iterator angle_iter;
	for(angle_iter=angleLST.begin();angle_iter!=angleLST.end();angle_iter++)
	{
		double angle1= *(angle_iter);
		angle1*=angle;
		RotateObjectY(angle1);
	}
	this->FinalTransformMatrix=InteractionMathematical->RoundTransformElemnt(this->FinalTransformMatrix);
	//this->FinalTransform->SetMatrix(this->FinalTransformMatrix);
}
//-------------------
void misInteractionObjectStyle::MoveObjectZ(double angle )
{
	
	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	misInteractionMathematicalAccount * InteractionMathematical=new misInteractionMathematicalAccount();

	//---- set camera position --------
	//SetCameraPositionforObjectRotate();
	//-------------------------------------
	doubleListTypeDef angleLST;
	angleLST=InteractionMathematical->FastSlowMotion();
	doubleListTypeDef::iterator angle_iter;
	for(angle_iter=angleLST.begin();angle_iter!=angleLST.end();angle_iter++)
	{
		double angle1= *(angle_iter);
		angle1*=angle;
		RotateObjectZ(angle1);
	}
	this->FinalTransformMatrix=InteractionMathematical->RoundTransformElemnt(this->FinalTransformMatrix);
	//this->FinalTransform->SetMatrix(this->FinalTransformMatrix);
}
//------------------------------------------------
vtkMatrix4x4* misInteractionObjectStyle::GetFinalTransformMatrix()
{
	return this->FinalTransformMatrix;
}

vtkTransform * misInteractionObjectStyle::GetFinalTransform()
{
   return this->FinalTransform;
}


void misInteractionObjectStyle::OnKeyDown()
{

	if (m_InitializeFlag)
	{
		this->SetInitialize();
		this->m_InitializeFlag=false;
	} 
	if (!(this->CurrentRenderer))
	{
		return;
	} 
	vtkMatrix4x4 * matrix=vtkMatrix4x4::New();
	//----------------------  
	vtkInteractorStyle::OnKeyDown();
	char * strControlKey=this->Interactor->GetKeySym();
	if(strControlKey[0]=='1')
	{
		MoveObjectX(90);
		matrix=GetFinalTransformMatrix();

	}
	else if(strControlKey[0]=='2')
	{
		MoveObjectX(-90);
		matrix=GetFinalTransformMatrix();

	}
	else if(strControlKey[0]=='3')
	{
		MoveObjectY(90);
		matrix=GetFinalTransformMatrix();

	}
	else if(strControlKey[0]=='4')
	{
		MoveObjectY(-90);
		matrix=GetFinalTransformMatrix();

	}
	else if(strControlKey[0]=='5')
	{
		MoveObjectZ(90);
		matrix=GetFinalTransformMatrix();

	}
	else if(strControlKey[0]=='6')
	{
		MoveObjectZ(-90);
		matrix=GetFinalTransformMatrix();
	}

	render->GetRenderWindow()->Render();
	render->GetActiveCamera()->SetClippingRange(-10000,10000);
}

void misInteractionObjectStyle::SetInitialize()
{
	//-------------
	this->FindPokedRenderer(this->Interactor->GetEventPosition()[0],
		this->Interactor->GetEventPosition()[1]);
	this->render=this->GetCurrentRenderer();
	//-------------
	double bounds[6];
	this->render->ComputeVisiblePropBounds(bounds);
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
}

void misInteractionObjectStyle::SetModel( vtkActorCollection * model)
{
  if (model)
  {
	  this->m_Model=model;
  }
}
//-------------------------------
