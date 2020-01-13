#pragma once

#define MAXNUMBEROFACTIVEVOLUME 4

#include "misSimpleQuadMapper.h"

class  vtkRenderer;
class misProxyMApper : public misSimpleQuadMapper
{

public:
	virtual void SetVolumeTextures(std::vector<voreen::VolumeHandle*>  handles);
	misProxyMApper(void);
	~misProxyMApper(void);
	virtual double *GetBounds();
	voreen::VolumeHandle* getHandle(int index);
	virtual void GetBounds(double bounds[6]);
	virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	void SetProxyPart1(std::vector<voreen::VolumeHandle*> handles);
	void AddTextures();
	vtkRenderer* GetRenderer() const { return renderer; }
	void SetRenderer(vtkRenderer* val) { renderer = val; }
	void SetProxyGeometry(voreen::MultiVolumeProxyGeometry* val);
	std::vector<voreen::VolumeHandle*> GetVolumeHandles() const { return m_VolumeHandles; }
protected:
	voreen::MultiVolumeProxyGeometry*            m_ProxyGeometry;
	std::vector<voreen::Processor*>  m_Processors;
	std::vector<voreen::VolumeHandle*>  m_VolumeHandles;	
	vtkRenderer*  renderer;
	
};

