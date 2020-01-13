#include "StdAfx.h"
#include "misEntryExitMapper.h"

using namespace std;
misEntryExitMapper::misEntryExitMapper(void)
{
	m_renderEntryToScene=false;
	m_renderExitToScene=false;
 	m_EntryExitProcess=new voreen::MeshEntryExitPoints;
	m_EntryExitProcess->SetOrder(1);
	m_Processors.push_back(m_EntryExitProcess);	
	m_Scales.resize(MAXNUMBEROFACTIVEVOLUME);				
	m_Translation.resize(MAXNUMBEROFACTIVEVOLUME);	
}


misEntryExitMapper::~misEntryExitMapper(void)
{
	delete m_EntryExitProcess;
}

void misEntryExitMapper::SetEntryExitPart( std::vector<voreen::VolumeHandle*> handles,tgt::ivec3 size )
{
	//check uinque
	SetProxyPart1(handles);
	if (!m_EntryExitProcess->isInitialized())
		{
			m_EntryExitProcess->initialize(size);
			m_EntryExitProcess->SetTestWithoutCheckPort(true);
			m_EntryExitProcess->SetRenderEntyToScene(m_renderEntryToScene);
			m_EntryExitProcess->SetRenderExitToScene(m_renderExitToScene);
			voreen::Port* poutProxy=m_ProxyGeometry->getPort("proxygeometry.geometry");
			voreen::Port* pinEntryExit=m_EntryExitProcess->getPort("proxygeometry.geometry");
			voreen::Port* pinEntryExitEnter=m_EntryExitProcess->getPort("image.entrypoints");
			voreen::Port* pinEntryExitExit=m_EntryExitProcess->getPort("image.exitpoints"); 
			poutProxy->connect(pinEntryExit);
		}
		
	for (int i=0;i<m_VolumeHandles.size();i++)
			m_VolumeHandles[i]->getVolume()->MatrixInitilize();
	auto SortFunc= [](voreen::Processor* a,voreen::Processor* b)->bool
	{
		return(a->GetOrder()<b->GetOrder());
	};
	sort(m_Processors.begin(),m_Processors.end(),SortFunc);
}

void misEntryExitMapper::Render( vtkRenderer *ren, vtkActor *a )
{
	//glEnable(GL_TEXTURE_2D); 
	glDisable(GL_TEXTURE_3D);
	SetCmaeraProp(ren);
	//glEnable(GL_COLOR_MATERIAL);
	std::for_each(m_Processors.begin(),m_Processors.end(),[&](voreen::Processor*  process)
	{
		process->beforeProcess();
		if (process->isReady())
			process->process();
		process->afterProcess();

	}); 
	
}

void misEntryExitMapper::SetCmaeraProp( vtkRenderer * ren )
{

	vtkCamera *cam = ren->GetActiveCamera();
	//cam->SetViewAngle(120);

	double focal[3];
	cam->GetFocalPoint(focal);	

	double posi[3];
	cam->GetPosition(posi);

	double upVec[3];
	cam->GetViewUp(upVec);


	tgt::Camera  camera_(tgt::vec3(posi[0],posi[1],posi[2]),  
		tgt::vec3(focal[0], focal[1], focal[2]),  
		tgt::vec3(upVec[0], upVec[1], upVec[2]));  

	double angle = cam->GetViewAngle();

	GLenum err = glGetError();

	if (err != GL_NO_ERROR) {
		const GLubyte* exp = gluErrorString(err);
	}
	int* size=ren->GetRenderWindow()->GetSize();
	double aspect = double(size[0]) /double(size[1]);

	double clip_range[2];
	cam->GetClippingRange(clip_range);
//	_ASSERT(clip_range[0]>0.01);
	tgt::Frustum* frust = new tgt::Frustum(angle,aspect,1,clip_range[1]);
	camera_.setFrustum(*frust);
	delete  frust;
	m_Camera = camera_;
	m_EntryExitProcess->SetCamera(camera_);

	float farDist = camera_.getFarDist();

	static int transValue = 0;
	if (transValue>60)
	{
		transValue = 0;
	}
	transValue++;
	err = glGetError();

	if (err != GL_NO_ERROR) {
		const GLubyte* exp = gluErrorString(err);
	}
	bool depth_Enabled = glIsEnabled(GL_DEPTH_TEST);
	GLint depth_values[1];
	glGetIntegerv(GL_DEPTH_FUNC,depth_values);

	GLboolean mask_values[1];
	glGetBooleanv(GL_DEPTH_WRITEMASK,mask_values);



	GLenum err1 = glGetError();

	if (err1 != GL_NO_ERROR) {
		const GLubyte* exp = gluErrorString(err1);
	}
	//	errorTex_->disable();

}


  




void misEntryExitMapper::SetRenderEntryToScene( bool val )
{
	m_renderEntryToScene = val;
	m_EntryExitProcess->SetRenderEntyToScene(val);
	
}

void misEntryExitMapper::SetRenderExitToScene( bool val )
{
	m_renderExitToScene = val;
	m_EntryExitProcess->SetRenderExitToScene(val);
}

void misEntryExitMapper::SetTransformToVolume( int index,tgt::mat4 matrix )
{
	voreen::Volume* volume=	m_VolumeHandles[index]->getVolume();
	auto preTrans=volume->getTransformation();
	tgt::mat4   newTrans=matrix*volume->GetDimensionTransform();
	volume->setTransformation(newTrans);
	volume->SetRelativeTransform(matrix);

}

void misEntryExitMapper::SetTransformToVolume( std::string name,tgt::mat4 matrix )
{
	int index=0;
	std::for_each(m_VolumeHandles.begin(),m_VolumeHandles.end(),[&](voreen::VolumeHandle* pHandle)
	{
 		voreen::VolumeMetaData meta = pHandle->getVolume()->meta();

		if (meta.getUnit() == name)
		{
			voreen::Volume*  PVolume=pHandle->getVolume();
			auto preTrans=PVolume->getTransformation();
			tgt::mat4   newTrans=matrix*PVolume->GetDimensionTransform();
			PVolume->setTransformation(newTrans);
		}
		index++;

	});

}

tgt::Camera misEntryExitMapper::GetCamera()
{
	return m_Camera;
}
