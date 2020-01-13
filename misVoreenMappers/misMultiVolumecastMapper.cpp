#include "StdAfx.h"
#include "misMultiVolumecastMapper.h"
#include "TransFuncIntensity.h"
using std::map;
using std::string;
using std::vector;

misMultiVolumecastMapper::misMultiVolumecastMapper(void)
{
	m_RayCasterProcess=new voreen::MultiVolumeRaycaster;
	m_RayCasterProcess->SetOrder(2);
	m_Processors.push_back(m_RayCasterProcess);
	//Note: this size is important and it must be transfered to application setting.
 	tgt::ivec3 size(512,512,1);
 	m_RayCasterProcess->initialize(size);
}


misMultiVolumecastMapper::~misMultiVolumecastMapper(void)
{
	delete  m_RayCasterProcess;
}

void misMultiVolumecastMapper::SetRayCastPart(std::map<misOpenglTexture* , voreen::VolumeHandle*> volumeHandleMap, std::map<misOpenglTexture* , ImageContainedTransferFuncs3D> textureMap,tgt::ivec3 size )
{
	map<misOpenglTexture* , voreen::VolumeHandle*>::iterator iter;
	std::vector<voreen::VolumeHandle*> handles;
	std::vector<ImageContainedTransferFuncs3D> TransferFunctions;

	for(iter = volumeHandleMap.begin(); iter!= volumeHandleMap.end(); iter++)
	{
		handles.push_back(iter->second);
		auto Tfs = textureMap.find(iter->first);
		if (Tfs != textureMap.end())
		{			
			TransferFunctions.push_back(Tfs->second);
		}
		else
			_ASSERT( 0 == 1);
	}
	_ASSERT(TransferFunctions.size() == handles.size());

	if( (m_VolumeHandles.size()==0)||(m_VolumeHandles.size()!=handles.size())||(!equal(handles.begin(),handles.end(),m_VolumeHandles.begin())))
	{
		SetEntryExitPart(handles,size);
		m_RayCasterProcess->SetEntryPort(m_EntryExitProcess->GetEntryRenderTarget());
		m_RayCasterProcess->SetExitPort(m_EntryExitProcess->GetExitRenderTarget());
	
		m_VolumeHandles=handles;
		for (int i=0;i<m_VolumeHandles.size();i++)
		{
			m_RayCasterProcess->SetVolumeHandle(i,m_VolumeHandles[i]);
			m_RayCasterProcess->SetTransferFunction(i,TransferFunctions[i]);

		}
	}

	SetLightSourceProperties(renderer);
}


void misMultiVolumecastMapper::Render( vtkRenderer *ren, vtkActor *a )
{
 
	SetCmaeraProp(ren);

	//glEnable(GL_COLOR_MATERIAL);
	std::for_each(m_Processors.begin(),m_Processors.end(),[&](voreen::Processor*  process)
	{
		process->beforeProcess();
		if (process->isReady())
			process->process();
		process->afterProcess();

	}); 

		SetLightSourceProperties(renderer);
	//m_Processors[0].

	//m_ProxyGeometry->TestResult();	
	//	renderQuad();
}

 

void misMultiVolumecastMapper::SetLightSourceProperties(vtkRenderer *rend)
{
	FillLightPropertyList();
	FillLightPropertyValueList(rend);
	double val[3];

	for (int i=0; i<4; i++)
	{
		const std::string lightPropID = lightSourcePropID[i];
		voreen::Property* Prop = m_RayCasterProcess->getProperty(lightPropID);
		voreen::FloatVec4Property *lightProp = dynamic_cast<voreen::FloatVec4Property*>(Prop);
		val[0] = lightSourcePropValue[i].x;
		val[1] = lightSourcePropValue[i].y;
		val[2] = lightSourcePropValue[i].z;

		if(lightProp)
		{
			lightProp->set(tgt::vec4(val[0],val[1],val[2],1.0));
		}
	}

	//		 light Attenuation 

	const std::string idlight0 = "applyLightAttenuation";
	voreen::Property* applyLightAttenuation = m_RayCasterProcess->getProperty(idlight0);
	voreen::BoolProperty *lightProp0 = dynamic_cast<voreen::BoolProperty*>(applyLightAttenuation);
	if(lightProp0)
	{
		lightProp0->set(false);
	}
}

void misMultiVolumecastMapper::FillLightPropertyList()
{
	lightSourcePropID[0] = "lightAmbient";
	lightSourcePropID[1] = "lightDiffuse";
	lightSourcePropID[2] = "lightPosition";
	lightSourcePropID[3] = "lightSpecular";
	lightSourcePropID[4] = "lightAttenuation";

}

void misMultiVolumecastMapper::FillLightPropertyValueList(vtkRenderer *rend)
{
	LightStruct lightstruct;

	lightstruct.x = 0.4;
	lightstruct.y = 0.4;
	lightstruct.z = 0.4; 
	lightSourcePropValue[0] = lightstruct;

	lightstruct.x = 0.5;
	lightstruct.y = 0.5;
	lightstruct.z = 0.5; 
	lightSourcePropValue[1] = lightstruct;

	vtkCamera *cam = rend->GetActiveCamera();
	double pos[3];
	cam->GetPosition(pos);
	lightstruct.x = pos[0];
	lightstruct.y = pos[1];
	lightstruct.z = pos[2]; 
	lightSourcePropValue[2] = lightstruct;

	lightstruct.x = 0.4;
	lightstruct.y = 0.4;
	lightstruct.z = 0.4; 
	lightSourcePropValue[3] = lightstruct;

	lightstruct.x = 1.0;
	lightstruct.y = 0.0;
	lightstruct.z = 0.0; 
	lightSourcePropValue[4] = lightstruct;
}

void misMultiVolumecastMapper::SetTransferFunctionan( int index, ImageContainedTransferFuncs3D transferFunction)
{
	m_RayCasterProcess->SetTransferFunction(index, transferFunction);
}


void misMultiVolumecastMapper::SetToolPosition( double x,double y ,double z )
{
	this->m_RayCasterProcess->SetToolPosition(tgt::vec3(x,y,z));
}

void misMultiVolumecastMapper::SetCropping( misCroppingDirectionInVR cropping )
{
	this->m_RayCasterProcess->SetCroppingDirection(cropping);
}

void misMultiVolumecastMapper::SetCmaeraProp( vtkRenderer * ren )
{
	misEntryExitMapper::SetCmaeraProp(ren);
	tgt::Camera cam = misEntryExitMapper::GetCamera();
	voreen::CameraProperty camProp("camera", "Camera", tgt::Camera(tgt::vec3(0.f, 0.f, 3.5f), tgt::vec3(0.f, 0.f, 0.f), tgt::vec3(0.f, 1.f, 0.f)));
	camProp.set(cam); 
	m_RayCasterProcess->SetCamera(camProp);
}

void misMultiVolumecastMapper::SetSampleRate(float sampleRate)
{
	m_RayCasterProcess->SetSampleRate(sampleRate);
}

void misMultiVolumecastMapper::ResetMapInShader()
{
	m_RayCasterProcess->ResetMapInShader();
}

misCroppingDirectionInVR misMultiVolumecastMapper::GetCropping()
{

	return m_RayCasterProcess->GetCroppingDirection();
}

void misMultiVolumecastMapper::CompileVolumeShader( int numberOfVol )
{
	m_RayCasterProcess->CompileVolumeShader(numberOfVol);
}
