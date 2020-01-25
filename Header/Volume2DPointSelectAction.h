#pragma once
#include "I3DViewer.h"
#include "misVolumeRendererContainer.h"
#include "IVolume3DRenderer.h"
#include "ILandmarkViewerCollection.h"

class Volume2DPointSelectAction : public vtkCommand
{
public:
	static Volume2DPointSelectAction* New();
	vtkBaseTypeMacro(Volume2DPointSelectAction, vtkCommand);
	void Create(std::shared_ptr<LandmarkDataAndType> , std::shared_ptr<ILandmarkViewer>, misVolumeRendererContainer::Pointer dummySubject);

	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;

private:
	std::shared_ptr<LandmarkDataAndType> m_LandmarkData;
	std::shared_ptr<ILandmarkViewer> m_LandmarkViewer;
	misVolumeRendererContainer::Pointer m_DummySubject;
};
