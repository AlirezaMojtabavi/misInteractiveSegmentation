#pragma once
#include "misEnums.h"
#include "VisualizationGeneralTypes.h"
#include "misStrctGUIModel.h"
#include "IVolumeSlicer.h"

class I3DLandmarkViewer;
class misGUIEvent;

class IGUIInteractionDispatchers
{
public:
	
	virtual bool ProccessEvents(misGUIEvent* pEvent) = 0;
	virtual void SetGUIModel(misStrctGUIModel guiModel) = 0;
	virtual void ResetZoomSetting() = 0;
	virtual misGeneralToolbarState GetLastState() = 0;
	virtual void SetLastStateToPan() = 0;
	virtual int GetCurrentZoomPercentage() = 0;
	virtual void SetCurrentZoomPercentage(int) = 0;
	virtual double GetImageZoomProportion() = 0;
	virtual void SetImageZoomProportion(double) = 0;
	virtual void SetImageOrintation(IMAGEORIENTATION) = 0;
	virtual IMAGEORIENTATION GetImageOrintation() = 0;
	virtual bool GetIsWindowSizeChanged() const = 0;
	virtual void SetIsWindowSizeChanged(bool val) = 0;
	virtual void ApplyMeasurmentToWindow(std::shared_ptr<IVolumeSlicer> , misGeneralToolbarState ) = 0;
	virtual void ApplyPanToWindow(std::shared_ptr<IVolumeSlicer>  viwer) = 0;
};
