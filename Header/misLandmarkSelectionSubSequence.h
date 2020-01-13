#pragma once

#include "ICoordinateSystemRenderer.h"
#include "misGroupViewer.h"
#include "misImageToPatientLandmarkBasedRegistation.h"
#include "misMultiViewSubSequence.h"
#include "misRegisterManagerTypes.h"
#include "misSubSequence.h"
#include "misViewingTypeColormapSelector.h"
#include "misobjectProperitiesEnums.h"
#include "ICheckVolumeRenderingSize.h"
#include "IDatasetManager.h"
#include "ILandmarkSelectionSSUIAdapter.h"
#include "IlandamrkSelectionSyncronizeLandamrks.h"
#include "IAddFixedLandmarks.h"
#include "IUpdateNextPoint.h"
#include "IValidLandmarksEnumerator.h"
#include "misValidLandmarksEnumerator.h"
#include "IModifyCurrentSelectedLandmark.h"
#include "misVolumeViewingTypes.h"
#include "misSubsequenceLayout.h"


class misLandmarkSelectionSubSequence : public misMultiViewSubSequence
{
public:

	misLandmarkSelectionSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICheckVolumeRenderingSize> volumeChecker,
		IDatasetManager* dataManager,
		std::shared_ptr<ILandmarkSelectionSSUIAdapter> uiAdapter,
		std::shared_ptr<IlandamrkSelectionSyncronizeLandamrks> landamrkSyncronizer,
		std::unique_ptr<IAddFixedLandmarks> landmarkAdder,
		std::shared_ptr<IImageToPatientLandmarkBasedRegistation> landmarkList,
		std::shared_ptr<IValidLandmarksEnumerator>,
		std::unique_ptr<IUpdateNextPoint> updateNextPoint,
		std::shared_ptr<IViewingTypeColormapSelector> , std::shared_ptr<misSoftwareInformation> softwareInformation);


	void SelectNewImageSetting(void);
	void UpdateGUI(void);
	misVolumeViewingTypes GetLastVolumeType();
	misCreateVariableWithSetGetMacro(ValidNearestDistanceOfLandmarks, double); // in mm
	void SetViewr(std::shared_ptr<INavigationViewersNView>  val);
	int m_MarkerIndexToAdd = 0;
	void DeleteLandmark(int index);
	void SetCurrentPackagUsed(std::shared_ptr<ISimpleDataPackage> package);
	bool ProcessRequest(misGUIEvent* pEvent) override;
	void SetRegistrationPoint();
	void AddNewEmptyPoint();
	void InitialeGuiProcessing();
	void OnSelected(void) override;
	void SelectModelType();
	void TaskOnLeave() override;
	void ResetSetting() override;
	void RealseAllResources() override;
	void UpdateSettingFromAppSetting(void) override;
	void Render(void) override;
	void AddRenderingTool(std::shared_ptr<ICoordinateSystemRenderer> renderingTool);
	std::shared_ptr<IImage> GetCurrentImage() const;
	void SetNormalizedVolumeThreshold(double newThreshold);
	void SelectVolumeType(misVolumeViewingTypes volumeType);
	bool ModifyCurrentSelectedLandmark(int landmarkIndex);

	misEventListTypedef GetEventToGui() override;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
	std::shared_ptr<ISimpleDataPackage> GetWorkingPackage() const;

private:

	void CompleteProcess(itk::Object *caller, const itk::EventObject& pEvent);
	void LoadPreviousLandmarks();
	void AddLandmarkToLandmarkList(misLandmarkInfoStruct lndStr);
	void UpdateLandmarkList(misLandmarkListTypdef landmarks);
	void RetriveDataList();
	void UpdateSubSeqState(void);
	void UpdateNextPoint(void);
	//find the number of valid landmarks and return that
	int GetNumberofCurrentValidLandmarks();
	void ShowToolsOff(void);

	void UpdateViewOnSelected(void);
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnloadedEvent();

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>> m_RenderingTools;
	int m_MinimumPointsForReg = 0;
	int m_MaxLandmark = 20.0;
	std::shared_ptr<IImage> m_CurrentImage;
	misSubsequenceLayout m_lndMarkSelctionSubTab;

	IDatasetManager* m_DataManger;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_pLandmarkList;
	int m_CurrentValidLandmarkNo = 0;
	int	m_CurrentSelectedLandmarkIndex = 0;
	struct misThreadContainer
	{
		std::shared_ptr<IImage>  m_image;
		misLandmarkSelectionSubSequence*  m_Instance;
	};
	double	m_LastUsedThreshold = 0.0;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	bool m_SetRegistrationPointRequestSent = false;
	std::shared_ptr<IViewingTypeColormapSelector> m_ViewingTypeColormapSelector;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ILandmarkSelectionSSUIAdapter> m_UiAdapter;
	std::shared_ptr<IlandamrkSelectionSyncronizeLandamrks> m_LandamrkSyncronizer;
	std::unique_ptr<IAddFixedLandmarks> m_LandmarksAdder;
	std::unique_ptr<IUpdateNextPoint> m_UpdateNextPoint;
	std::shared_ptr<IValidLandmarksEnumerator> m_ValidLandmarksEnumerator;
	std::shared_ptr<IModifyCurrentSelectedLandmark> m_LandmarkModifier;
};
