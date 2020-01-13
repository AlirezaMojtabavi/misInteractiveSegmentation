#pragma once

class misVoreenActor :	public vtkOpenGLActor
{
private:
	misVoreenActor(void);
public:

		static  misVoreenActor* New();
		virtual int RenderVolumetricGeometry( vtkViewport *);
		 virtual int RenderOpaqueGeometry(vtkViewport *viewport);
	~misVoreenActor(void);
};

