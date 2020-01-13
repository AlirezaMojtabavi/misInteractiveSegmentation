#include "StdAfx.h"
#include "misProxyMApper.h"

#include "misDIRReader.h"
#include "misImage.h"
#include "misOpenglTexture.h"
#include "misMathUtils.h"

using namespace std;
misProxyMApper::misProxyMApper(void)
{
	m_ProxyGeometry=NULL;
}

misProxyMApper::~misProxyMApper(void)
{
	delete  m_ProxyGeometry;
}

void misProxyMApper::SetProxyGeometry( voreen::MultiVolumeProxyGeometry* val )
{
	m_ProxyGeometry = val;
}

void misProxyMApper::SetVolumeTextures(std::vector<voreen::VolumeHandle*>  handles)
{

	m_ProxyGeometry->ResetVolumeData();

		for_each(m_VolumeHandles.begin(),m_VolumeHandles.end(),[&](voreen::VolumeHandle*  pHandle)
		{
			//add and make it uinque
			m_ProxyGeometry->AddVolumeHandle(pHandle);
		});
	
}

void misProxyMApper::SetProxyPart1( std::vector<voreen::VolumeHandle*> handles )
{
	m_VolumeHandles=handles;
	char* argv[1];
	argv[0] = "rama";

	if (!m_ProxyGeometry)
	{
		m_ProxyGeometry=new voreen::MultiVolumeProxyGeometry();
		m_ProxyGeometry->SetOrder(0);
		m_Processors.push_back(m_ProxyGeometry);
		m_ProxyGeometry->initialize();
	}

	SetVolumeTextures(m_VolumeHandles);
}

void misProxyMApper::Render( vtkRenderer *ren, vtkActor *a )
{	
	glEnable(GL_TEXTURE_2D); 
	glDisable(GL_TEXTURE_3D);
	//glEnable(GL_LIGHTING);
	//glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_COLOR_MATERIAL);
	for_each(m_Processors.begin(),m_Processors.end(),[&](voreen::Processor*  process)
	{
	process->beforeProcess();
	if (process->isReady())
	process->process();
	process->afterProcess();

	}); 

	 
m_ProxyGeometry->TestResult();	
//	renderQuad();
 
}

double * misProxyMApper::GetBounds()
{
	std::fill(Bounds, Bounds + 6, 0);
	for (auto volumeHandle : m_VolumeHandles)
	{
		tgt::ivec3  dims = volumeHandle->getVolume()->getDimensions();
		tgt::vec3  spac = volumeHandle->getVolume()->getSpacing();
		double bounds[6];
		bounds[0] = 0;
		bounds[1] = dims[0] * spac[0];
		bounds[2] = 0;
		bounds[3] = dims[1] * spac[1];
		bounds[4] = 0;
		bounds[5] = dims[2] * spac[2];
		misMathUtils::MergeBounding(Bounds, bounds, Bounds);
	}
	return  Bounds;
}

void misProxyMApper::GetBounds( double bounds[6] )
{
	this->GetBounds();
	for (int i=0; i<6; i++)
	{
		bounds[i] = this->Bounds[i];
	}
}

voreen::VolumeHandle* misProxyMApper::getHandle( int index )
{

	if (index<m_VolumeHandles.size())
	{
		return m_VolumeHandles[index];
	}
	else
		return NULL;
}


