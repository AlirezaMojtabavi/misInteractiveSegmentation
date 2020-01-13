 #pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DViewer.h"

// Test adding and updating view of landmarks
class misSimple3DViewerTest :
	public misIntegrationTestApplication
{
public:
	misSimple3DViewerTest(int &argc, char ** argv);
	void AddSphere() const;
	void AddSTLs() const;
	void InitVolumeRendering();
	virtual void PulseHandler();
private:
	vtkSphereSource *m_Sphere;
	std::shared_ptr<Iwindows> m_wnd; 
	std::shared_ptr<I3DViewer>   m_Viewer;
	vtkSphereSource* m_Sphere01;
};

