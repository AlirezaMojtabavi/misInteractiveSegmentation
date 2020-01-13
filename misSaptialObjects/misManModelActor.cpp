#include "StdAfx.h"
#include "misManModelActor.h"
#include "misCameraMacher.h"

misManModelActor::misManModelActor(void)
	:m_LastResult(vtkSmartPointer<vtkMatrix4x4>::New()), m_MatrixInilized(false)
{
	m_Windowsize[0] = 0;
	m_Windowsize[1] = 1;
}

misManModelActor::~misManModelActor(void)
{
}

// Copy the follower's composite 4x4 matrix into the matrix provided.
void misManModelActor::GetMatrix(vtkMatrix4x4 *result)
{
	auto windowSize = m_Renderer->GetRenderWindow()->GetSize();
	bool windowSizeChanged = (m_Windowsize[0] != windowSize[0]) || (m_Windowsize[1] != windowSize[1]);
	auto manModelDesiredPosition = CalculateManModelDesiredPosition();
	double worldRUPt[4];
	GetRightUpPoint(manModelDesiredPosition, worldRUPt);
	double worldLUPt[4];
	GetLeftUpPoint(manModelDesiredPosition, worldLUPt);
	double worldRDPt[4];
	m_Renderer->SetViewPoint(1.0, -1.0, manModelDesiredPosition);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldRDPt);
	double height[3];
	for (int i=0;i<3;i++)
		height[i]=worldRDPt[i]-worldRUPt[i];
	double heightInWordldCoordinate = vtkMath::Dot(height,height);
	heightInWordldCoordinate = sqrt(heightInWordldCoordinate);

	double width[3];
	for (auto i=0; i<3 ;i++)
		width[i] = worldRUPt[i] - worldLUPt[i];
	double widthInWordldCoordinate = vtkMath::Dot(width,width);
	widthInWordldCoordinate = sqrt(widthInWordldCoordinate);


	//	float m_3DZoomScaleFactor=lenght /500.0;	 
	float m_3DZoomScaleFactor = 1;	 
	if (heightInWordldCoordinate>widthInWordldCoordinate)
		m_3DZoomScaleFactor=widthInWordldCoordinate /m_ScaleRatio;	 
	else
		m_3DZoomScaleFactor=heightInWordldCoordinate /m_ScaleRatio;	
	Transform->Push();  
	Transform->PostMultiply();  
	Transform->Identity();
	bool  parallelProjection = (bool)m_Renderer->GetActiveCamera()->GetParallelProjection();
	double manPosition[4];
	int* size=m_Renderer->GetRenderWindow()->GetSize();
	int displayCoord[2];
	if (parallelProjection)
	{
		float val1=m_ParallelOffset[0]*(float(size[0])/700.0);
		displayCoord[0]=size[0]-val1;
		float val2=m_ParallelOffset[1]*(float(size[1])/700.0);
		displayCoord[1]=size[1]-val2;

	}
	else
	{
		displayCoord[0]=size[0]-m_Offset[0];
		displayCoord[1]=size[1]-m_Offset[1];

	}
	double* bound=GetBounds();
	m_Renderer->SetDisplayPoint(displayCoord[0],displayCoord[1], manModelDesiredPosition);
	m_Renderer->DisplayToWorld();
	m_Renderer->GetWorldPoint(manPosition);
	if (!parallelProjection)
		ModifyManModelOrientation(manPosition);
	Transform->Scale(  m_3DZoomScaleFactor, m_3DZoomScaleFactor,  m_3DZoomScaleFactor);
 	Transform->Translate(manPosition);
 	Transform->GetMatrix(result);  
	m_LastResult->DeepCopy(result);
	m_MatrixInilized = true;
	m_Windowsize[0] = windowSize[0];
	m_Windowsize[1] = windowSize[1];
	Transform->Pop();  

} 

void misManModelActor::GetLeftUpPoint(double manModelDesiredPosition, double* worldRDPt)
{

	m_Renderer->SetViewPoint(1.0, -1.0, manModelDesiredPosition);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldRDPt);

	double worldLDPt[4];
	m_Renderer->SetViewPoint(-1.0, -1.0, manModelDesiredPosition);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldLDPt);
	if (worldLDPt[3])
	{
		worldLDPt[0] /= worldLDPt[3];
		worldRDPt[1] /= worldLDPt[3];
		worldLDPt[2] /= worldLDPt[3];
		worldLDPt[3] = 1.0;
	}
}

void misManModelActor::GetRightUpPoint(double manModelDesiredPosition, double* worldRUPt)
{


	m_Renderer->SetViewPoint(1.0, 1.0, manModelDesiredPosition);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldRUPt);

	double worldLUPt[4];
	m_Renderer->SetViewPoint(-1.0, 1.0, manModelDesiredPosition);
	m_Renderer->ViewToWorld();
	m_Renderer->GetWorldPoint(worldLUPt);

	if (worldLUPt[3])
	{
		worldLUPt[0] /= worldLUPt[3];
		worldLUPt[1] /= worldLUPt[3];
		worldLUPt[2] /= worldLUPt[3];
		worldLUPt[3] = 1.0;
	}
}

double misManModelActor::CalculateManModelDesiredPosition()
{
	double objectToCmeraVector[3];
	GetObjectToCameraVector(objectToCmeraVector);
	auto objectToCmeraVectorLenght = vtkMath::Norm(objectToCmeraVector);
	auto frustumRange = m_Renderer->GetActiveCamera()->GetClippingRange();
	auto frustumLenght = frustumRange[1] - frustumRange[0];
	return ((objectToCmeraVectorLenght / frustumLenght) * 0.5);
}

void misManModelActor::ModifyManModelOrientation(double* worldPt){

	// ManModelPos: the world coordinates of the man model
	double ManModelPos[3];
	
	ManModelPos[0] = worldPt[0];
	ManModelPos[1] = worldPt[1];
	ManModelPos[2] = worldPt[2];



	double OC[3], MC[3];
	double PI = 3.14159265;

	GetObjectToCameraVector(OC);

	 
	double OCsize = sqrt(pow(OC[0],2) + pow(OC[1],2) + pow(OC[2],2));
	// the view vector from camera to the Man Model Position
	double CameraPos[3];
	m_Renderer->GetActiveCamera()->GetPosition(CameraPos);
	MC[0] = ManModelPos[0]-CameraPos[0];
	MC[1] = ManModelPos[1]-CameraPos[1];
	MC[2] = ManModelPos[2]-CameraPos[2];

	// Calculate the angle between OC and MC vectors 
	//Np: the rotation axis around which we will rotate the MC to be view as OC
	//teta: the view angle difference of OC and MC
	double teta, Np[3];
	
	
	double MCsize = sqrt(pow(MC[0],2) + pow(MC[1],2) + pow(MC[2],2));	
	teta = acos((OC[0]*MC[0] + OC[1]*MC[1] + OC[2]*MC[2])/(OCsize*MCsize)) * 180.0 / PI;


	vtkMath::Normalize(OC);
	vtkMath::Normalize(MC);
	//Compute cross product of the OC and MC vectors to find the rotation axis
	Np[0] = OC[1]*MC[2] - OC[2]*MC[1];//y* -z*
	Np[1] = OC[2]*MC[0] - OC[0]*MC[2];//z* -x*
	Np[2] = OC[0]*MC[1] - OC[1]*MC[0];//x* -y*
	vtkMath::Normalize(Np);

}

void misManModelActor::GetObjectToCameraVector(double * OC)
{
	// The view vector from camera to object position
	double CameraPos[3];
	m_Renderer->GetActiveCamera()->GetPosition(CameraPos);
	OC[0] = m_ObjectPosition[0] - CameraPos[0];
	OC[1] = m_ObjectPosition[1] - CameraPos[1];
	OC[2] = m_ObjectPosition[2] - CameraPos[2];
}

misManModelActor* misManModelActor::New()
{
	double offset[2];
	offset[0]=75;offset[1]=75;
	misManModelActor* manModel=new misManModelActor();
	manModel->SetOffset(offset);
	manModel->SetScaleRatio(500);

	return manModel;
	
}
