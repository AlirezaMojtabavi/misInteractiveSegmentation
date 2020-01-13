#include "StdAfx.h"
#include "misViewDependentActor.h"

#include "misViewDependentActor.h"

vtkStandardNewMacro(misViewDependentActor);

vtkCxxSetObjectMacro(misViewDependentActor,m_Renderer,vtkRenderer);

float misViewDependentActor::NearPlaneArea(vtkTransform* pTransform)
{

	double*  bounding=this->GetBounds();
	double positionMin[4];
	positionMin[0]=bounding[0];
	positionMin[1]=bounding[2];
	positionMin[2]=bounding[4];
	positionMin[3]=1;
	
	double positionMax[4];
	positionMax[0]=bounding[1];
	positionMax[1]=bounding[3];
	positionMax[2]=bounding[5];
	positionMax[3]=1;
	float lenght=1;
 	if (pTransform)
	{
		double positionMinTr[4];
		double positionMaxTr[4];

		auto *position1= pTransform->TransformDoublePoint(positionMin);
		for (int i=0;i<3;i++)
			positionMinTr[i]=position1[i];
		auto position2= pTransform->TransformDoublePoint(positionMax);

		for (int i=0;i<3;i++)
			positionMaxTr[i]=position2[i];

		double viewPoint1[3];
		this->m_Renderer->SetWorldPoint(positionMinTr);
		this->m_Renderer->WorldToView();
		this->m_Renderer->GetViewPoint(viewPoint1);

		double viewPoint2[4];
		this->m_Renderer->SetWorldPoint(positionMaxTr);
		this->m_Renderer->WorldToView();
		this->m_Renderer->GetViewPoint(viewPoint2);


		double width[3];
		for (int i=0;i<3;i++)
			width[i]=viewPoint1[i]-viewPoint2[i];
		lenght=vtkMath::Dot(width,width);
	}
	return lenght; 
}

// Creates a follower with no camera set
misViewDependentActor::misViewDependentActor()
{
  this->m_Renderer = NULL;
  this->Device = vtkActor::New();
  this->Camera=0;
}

misViewDependentActor::~misViewDependentActor()
{
  if (this->m_Renderer)
    {
    this->m_Renderer->UnRegister(this);
    }
  
  this->Device->Delete();
}

// Copy the follower's composite 4x4 matrix into the matrix provided.
void misViewDependentActor::GetMatrix(vtkMatrix4x4 *result)
{
	 double p1[3];
	

	float lenght=0;
	lenght = DistanceToCamera();
	bool parallell=false;
	float parallellScale=1;

	if (m_Renderer)
	{
		  parallell=(bool)m_Renderer->GetActiveCamera()->GetParallelProjection();
		  parallellScale=m_Renderer->GetActiveCamera()->GetParallelScale();
	}

//	float m_3DZoomScaleFactor=2;
	this->Transform->Push();  
	this->Transform->PostMultiply();  
	this->Transform->Identity();
	this->GetOrientation();


	// apply user defined matrix last if there is one 
	if (this->UserMatrix)
	{
		this->Transform->Concatenate(this->UserMatrix);
	}

	this->Transform->Translate(-this->Origin[0],
		-this->Origin[1],
		-this->Origin[2]);
	// scale
	//this->Transform->Scale(m_3DZoomScaleFactor,
	//	m_3DZoomScaleFactor,
	//	m_3DZoomScaleFactor);

	// rotate
	this->Transform->RotateY(this->Orientation[1]);
	this->Transform->RotateX(this->Orientation[0]);
	this->Transform->RotateZ(this->Orientation[2]);
	// scale
	//this->Transform->Scale(this->Scale[0],
	//	this->Scale[1],
	//	this->Scale[2]);

	//this->Transform->Scale(  m_3DZoomScaleFactor, m_3DZoomScaleFactor,  m_3DZoomScaleFactor);
	p1[0] = this->Origin[0] + this->Position[0];
	p1[1] = this->Origin[1] + this->Position[1];
	p1[2] = this->Origin[2] + this->Position[2];	
	vtkTransform* ptrnsform=vtkTransform::New();
	ptrnsform->DeepCopy(Transform);
	ptrnsform->Scale(this->Scale[0],
		this->Scale[1],
		this->Scale[2]);
	//ptrnsform->tr
	ptrnsform->Translate(-p1[0],-p1[1],-p1[2]);	

	//float scale=NearPlaneArea(ptrnsform);
	float m_3DZoomScaleFactor=sqrt(lenght)/sqrt(45000.0f) ;
	//float m_3DZoomScaleFactor=0.05f/sqrt(scale);

	if (parallell)
	{
		this->Transform->Scale(  parallellScale/100, parallellScale/100,  parallellScale/100);

	}

	else

		this->Transform->Scale(  m_3DZoomScaleFactor, m_3DZoomScaleFactor,  m_3DZoomScaleFactor);
	this->Transform->Translate(p1[0],p1[1],p1[2]);	

	 


	this->Transform->GetMatrix(result);  
	this->Transform->Pop();  
	ptrnsform->Delete();
} 

void misViewDependentActor::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);
   
}

int misViewDependentActor::RenderOpaqueGeometry(vtkViewport *vp)
{
  if ( ! this->Mapper )
    {
    return 0;
    }

  if (!this->Property)
    {
    // force creation of a property
    this->GetProperty();
    }

  if (this->GetIsOpaque())
    {
    vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
    this->Render(ren);
    return 1;
    }
  return 0;
}

//-----------------------------------------------------------------------------
int misViewDependentActor::RenderTranslucentPolygonalGeometry(vtkViewport *vp)
{
  if ( ! this->Mapper )
    {
    return 0;
    }

  if (!this->Property)
    {
    // force creation of a property
    this->GetProperty();
    }

  if (!this->GetIsOpaque())
    {
    vtkRenderer *ren = static_cast<vtkRenderer *>(vp);
    this->Render(ren);
    return 1;
    }
  return 0;
}

//-----------------------------------------------------------------------------
// Description:
// Does this prop have some translucent polygonal geometry?
int misViewDependentActor::HasTranslucentPolygonalGeometry()
{
  if ( ! this->Mapper )
    {
    return 0;
    }
  // make sure we have a property
  if (!this->Property)
    {
    // force creation of a property
    this->GetProperty();
    }

  // is this actor opaque ?
  return !this->GetIsOpaque();
}

//-----------------------------------------------------------------------------
// This causes the actor to be rendered. It, in turn, will render the actor's
// property and then mapper.  
void misViewDependentActor::Render(vtkRenderer *ren)
{
	m_Renderer=ren;
  this->Property->Render(this, ren);
  
  vtkMatrix4x4 *matrix = vtkMatrix4x4::New();
  
  this->Device->SetProperty (this->Property);
  this->Property->Render(this, ren);
  if (this->BackfaceProperty)
    {
    this->BackfaceProperty->BackfaceRender(this, ren);
    this->Device->SetBackfaceProperty(this->BackfaceProperty);
    }

    
  // make sure the device has the same matrix
  this->GetMatrix(matrix);
  this->Device->SetUserMatrix(matrix);
  
  this->Device->Render(ren,this->Mapper);

  matrix->Delete();
}

void misViewDependentActor::GetMatrix(double m[16])
{
  this->GetMatrix(this->Matrix); 
  vtkMatrix4x4::DeepCopy(m,this->Matrix);
}

void misViewDependentActor::ShallowCopy(vtkProp *prop)
{
  misViewDependentActor *f = misViewDependentActor::SafeDownCast(prop);
  if ( f != NULL )
    {
    this->Setm_Renderer(f->Getm_Renderer());
    }

  // Now do superclass 
  this->vtkActor::ShallowCopy(prop);
}

void misViewDependentActor::SetCamera( vtkCamera* pCamera )
{
	this->Camera=pCamera;

}

void misViewDependentActor::SetObjectPosition(double ObjectPos[3]){
	m_ObjectPosition[0] = ObjectPos[0];
	m_ObjectPosition[1] = ObjectPos[1];
	m_ObjectPosition[2] = ObjectPos[2];
}

void misViewDependentActor::ModifyManModelOrientation(double* worldPt){

	// ManModelPos: the world coordinates of the man model
	double CameraPos[3], ManModelPos[3];
	m_Renderer->GetActiveCamera()->GetPosition(CameraPos);	
	ManModelPos[0] = worldPt[0];
	ManModelPos[1] = worldPt[1];
	ManModelPos[2] = worldPt[2];

	double ObjectPos[3];// The position of object in the world
	ObjectPos[0] = m_ObjectPosition[0];
	ObjectPos[1] = m_ObjectPosition[1];
	ObjectPos[2] = m_ObjectPosition[2];

	double OC[3], MC[3];
	double PI = 3.14159265;

	// The view vector from camera to object position
	OC[0] = ObjectPos[0]-CameraPos[0];
	OC[1] = ObjectPos[1]-CameraPos[1];
	OC[2] = ObjectPos[2]-CameraPos[2];
	// the view vector from camera to the Man Model Position
	MC[0] = ManModelPos[0]-CameraPos[0];
	MC[1] = ManModelPos[1]-CameraPos[1];
	MC[2] = ManModelPos[2]-CameraPos[2];

	// Calculate the angle between OC and MC vectors 
	//Np: the rotation axis around which we will rotate the MC to be view as OC
	//teta: the view angle difference of OC and MC
	double teta, Np[3];
	double OCsize, MCsize; 
	OCsize = sqrt(pow(OC[0],2) + pow(OC[1],2) + pow(OC[2],2));
	MCsize = sqrt(pow(MC[0],2) + pow(MC[1],2) + pow(MC[2],2));	
	teta = acos((OC[0]*MC[0] + OC[1]*MC[1] + OC[2]*MC[2])/(OCsize*MCsize)) * 180.0 / PI;

	//Compute cross product of the OC and MC vectors to find the rotation axis
	Np[0] = OC[1]*MC[2] - OC[2]*MC[1];//y* -z*
	Np[1] = OC[2]*MC[0] - OC[0]*MC[2];//z* -x*
	Np[2] = OC[0]*MC[1] - OC[1]*MC[0];//x* -y*
	this->Transform->RotateWXYZ(teta,Np[0],Np[1],Np[2]);
	
}

float misViewDependentActor::DistanceToCamera(  )
{
	float lenght=0;
	if (m_Renderer)
	{
		vtkCamera* pCam= m_Renderer->GetActiveCamera();
		double* positionCam=pCam->GetPosition();
		double width[3];
		this->GetPosition(m_ObjectPosition);
		for (int i=0;i<3;i++)
			width[i]=m_ObjectPosition[i]-positionCam[i];
		lenght=vtkMath::Dot(width,width);

	}	return lenght;
}
