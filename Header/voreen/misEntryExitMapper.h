#pragma once

#include "misProxyMApper.h"

namespace voreen
{
	class MeshEntryExitPoints;
	 
}
class misEntryExitMapper : public misProxyMApper
{
	friend class misEntryExitTest;

	protected:
		voreen::MeshEntryExitPoints*       m_EntryExitProcess;
		bool	m_renderEntryToScene;
		bool	m_renderExitToScene;

 	
 		std::vector<tgt::mat4>           m_Scales;
 		std::vector<tgt::mat4>           m_Translation;
		tgt::Camera	m_Camera;
	
		
public:
	
	tgt::Camera		GetCamera();
	virtual void	Render(vtkRenderer *ren, vtkActor *a);
	virtual void	SetCmaeraProp( vtkRenderer * ren );
	
	void	SetEntryExitPart(std::vector<voreen::VolumeHandle*> handles,tgt::ivec3 size);
	void	SetRenderEntryToScene(bool val);
	void	SetRenderExitToScene(bool val);
	void	SetTransformToVolume(int index,tgt::mat4 matrix);
	void	SetTransformToVolume(std::string  name,tgt::mat4 matrix);
	
	misEntryExitMapper(void);
	~misEntryExitMapper(void);
	
};

