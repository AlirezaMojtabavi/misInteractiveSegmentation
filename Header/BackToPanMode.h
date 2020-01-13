#pragma once
#include "misCoreEvents.h"
#include <misAutoMeasurment.h>
#include <I3DViewer.h>
#include "IBackToPanMode.h"
#include "misVolumeRendererContainer.h"

class BackToPanMode : public IBackToPanMode
{
public:
	BackToPanMode(misMeasurment::Pointer, vtkSmartPointer<misInteractorSTyleImageExtend>, std::shared_ptr<I3DViewer>,
		misVolumeRendererContainer::Pointer

	);
 
	void Update() override;
	void SetControlToPan() override;
	void ResetGeneralToolbarState() const override;

private:
	void UpdateImageInteractionState();
	void ResetGeneralToolbarInRightClick();

	misMeasurment::Pointer m_MeasurmentService;
	misGeneralToolbarState m_GeneralToolbarState;
	vtkSmartPointer<misInteractorSTyleImageExtend> m_pImageStyle;
	std::shared_ptr<I3DViewer> m_3DViewer;
	misVolumeRendererContainer::Pointer m_DummyObject;

};

