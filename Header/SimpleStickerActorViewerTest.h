#pragma once
#include "misIntegrationTestApplication.h"
#include "mis3DViewer.h"
#include "misStickerModelActor.h"

class newStickerModelActor : public misStickerModelActor
{

public:
	virtual void GetMatrix(vtkMatrix4x4 *m) override;
	static newStickerModelActor *New(double scaleRatio, double* offset)
	{
		newStickerModelActor*  sticker = new newStickerModelActor();
		sticker->SetScaleRatio(scaleRatio);
		sticker->SetOffset(offset);
		return sticker;
	}


};
// Test adding and updating view of landmarks
class SimpleStickerActorViewerTest :
	public misIntegrationTestApplication
{
public:
	SimpleStickerActorViewerTest(int &argc, char ** argv);
	void AddSphere() ;
	
	virtual void PulseHandler();
private:
	vtkConeSource *arrow;
	std::shared_ptr<Iwindows> m_wnd;
	std::shared_ptr<I3DViewer>   m_Viewer;
	vtkConeSource* m_Sphere01;
 	vtkSmartPointer<vtkFollower> m_StickerActor_second;

	double offset[2] = { 300, 300 };
	double scale = 50.0;
	vtkSmartPointer<vtkFollower> m_StickerActor_text;
};



