#pragma once

#include "IGUIInteractionDispatchers.h"
#include "IViewerRepository.h"
#include "misVolumeSlicer.h"
#include "misStrctGUIModel.h"
#include "ImageViewersSliderEventHandler.h"
#include "misEventFromGui.h"

class misApplicationSetting;

class misGUIInteractionDispatchers  : public IGUIInteractionDispatchers
{
public:

	misGUIInteractionDispatchers(std::shared_ptr<IViewerRepository> repo);
	bool ProccessEvents(misGUIEvent* pEvent) override;
	void SetGUIModel(misStrctGUIModel guiModel) override;
	void ResetZoomSetting() override;
	misGeneralToolbarState GetLastState() override;
	void SetLastStateToPan() override;
	int GetCurrentZoomPercentage() override;
	void SetCurrentZoomPercentage(int) override;
	double GetImageZoomProportion() override;
	void SetImageZoomProportion(double) override;
	void SetImageOrintation(IMAGEORIENTATION)override;
	IMAGEORIENTATION GetImageOrintation()override;
	bool GetIsWindowSizeChanged() const override;
	void SetIsWindowSizeChanged(bool val) override;
	void ApplyMeasurmentToWindow(std::shared_ptr<IVolumeSlicer>  viwer, misGeneralToolbarState ls) override;
	void ApplyPanToWindow(std::shared_ptr<IVolumeSlicer>  viwer) override;


private:
	bool CheckWindowSize(misGUIEvent* pEvent);

	void  SetSlider(misGUIEvent * EV);

	void SynchronizeSliders(misGUIEvent * EV);

	bool SetResetContrast(misGUIEvent * EV);
	bool PresetContrast(misGUIEvent * EV);
	bool ApplyResetContrastToWindow(std::shared_ptr<IVolumeSlicer>  viwer);
	bool ApplyPresetContrastToWindow(std::shared_ptr<IVolumeSlicer>  viwer, misImageViewingType viewingType);
	bool SetContrast(misGUIEvent * EV);
	bool  ApplyContrastToWindow(std::shared_ptr<IVolumeSlicer> viewer2D);

	void  SetPan(misGUIEvent * EV);
	void SetRotate(misGUIEvent * EV);

	void Set3DRotate(misGUIEvent * EV);

	void  Set3DPan(misGUIEvent * EV);
	void  Set2DPan(misGUIEvent * EV);


	void  SetAllReset(misGUIEvent * EV);
	void  Set3DAllReset(misGUIEvent * EV);
	void  SetZoom(misGUIEvent * EV);

	void  Set2DZoom(misGUIEvent * EV);
	void Apply2DZoomToWindow(std::shared_ptr<IVolumeSlicer>  viwer, misZoomState zoomState);
	void Apply3DZoomToWindow(std::shared_ptr<IVolume3DRenderer> viwer, misZoomEvent* eventData);
	void  Set3DZoom(misGUIEvent * EV);
	void  MeasurmentCotrol(misGUIEvent *EV);
	void  AutoMeasurmentCotrol(misGUIEvent *EV);
	void ApplyAutoMeasurmentToWindow(std::shared_ptr<IVolumeSlicer>  viwerer, bool activate);

	void  PanMode(misGUIEvent *EV);
	void UpdatePanMode(std::shared_ptr<IVolumeSlicer> viewer2D);

	void  SetAnteriorView(HWND   handle);
	void  SetPosteriorView(HWND   handle);
	void  SetInferiorView(HWND   handle);
	void  SetSupreiorView(HWND   handle);
	void  SetLeftView(HWND   handle);
	void  SetRightView(HWND   handle);

	misStrctGUIModel  m_guiModel;
	misApplicationSetting*     m_AppSetting;
	misGeneralToolbarState	   m_LastState;
	bool					   m_AutoMeasurmentIsActived;
	int					       m_CurrentZoomPercentage;
	double                     m_CurrentZoomProportion;
	bool					   m_ContrastSetting;
	IMAGEORIENTATION    m_ChanegedWindowOrientation; //when window size is changed, its Orientation must be saved in order to Update

	std::shared_ptr<IViewerRepository> m_ViewerRepository;
	bool m_SettingPositionBySliceNumber = false;
	bool m_IsWindowSizeChanged;
	ImageViewersSliderEventHandler m_SliderEventHandler;
};
