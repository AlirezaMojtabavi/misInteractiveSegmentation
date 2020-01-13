#pragma once

#include "IDatasetManager.h"
#include "IImage.h"
#include "INavigationViewersNView.h"
#include "misDatasetManager.h"
#include "misEventFromGui.h"
#include "misMultiViewSubSequence.h"
#include "misVoreenRepresentation.h"
#include "ICorrectionTransformBox.h"
#include "IVolume3DRenderer.h"
#include "IVolumeMaker.h"
#include "IVolumeThreshold.h"
#include "VolumeThreshold.h"

class MIS3DInteractionStyle;
class misImageDirectionCalculation;
class vtkMatrix4x4;
class vtkTransform;

namespace parcast
{
	class IDataCheckingUiUpdater;
	class IVolumeThresholdSliderRangeUpdater;
}

class  misDataCheckingSubSeq : public misMultiViewSubSequence, 
	public std::enable_shared_from_this<misDataCheckingSubSeq>
{

public:
	class misBoxObserver : public vtkCommand
	{
	public:
		void SetDataChecking(std::shared_ptr<misDataCheckingSubSeq> datachecking);
		static misBoxObserver* New();
		virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData);

	private:
		std::shared_ptr<misDataCheckingSubSeq>  m_DataCheckingSubSeq;
	};

	misDataCheckingSubSeq(
			std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager,
		std::shared_ptr<parcast::IVolumeMaker> volumeMaker, std::shared_ptr<misSoftwareInformation> softwareInformation);

	misDataCheckingSubSeq(
	 IDatasetManager* dataSetManger,
		std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<INavigationViewersNView> viewer, std::shared_ptr<misSoftwareInformation> softwareInformation);

	void UpdateStatus(long long int puls);
	void OnSelected(void);
	void UpdateSettingFromAppSetting(void);
	void UpdateGUIStateOnFaceSelection();
	bool ProcessRequest(misGUIEvent* pEvent);
	void UpdateBySelectedFace(misTextureEnum appliedTexture);
	void UpdateFaceSettingState();
	void SetVolumeThreshold(double threshold, misApplicationType appType);
	// Apply the correction transform internally to the image and all other fMRI images that are related to it (if any).
	void AcceptDirection(vtkMatrix4x4* directionCorrectionMatrix);
	void Render(void);
	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:

	void ShowImage(misUID newObject, misApplicationType appType);
	void CheckToSHowCorrectionBox();
	void Initialize();
	void DenyDirection();
	void ResetDirection();
	bool AcceptROI();
	void GenerateRoiImageName(std::shared_ptr<IImage> ROIImage);
	// Removes the ROI widget from the scene and the ROI bounds from the image data and updates the 3D scene.
	void RemoveROI();
	void UpdateFaceSelection(misTextureEnum appliedTexture);
	void UpdateListInGUI(void);
	void TaskOnLeave(void);
	void UpdateReadyForLeaveStatus(void);
	void ObserveRoiReaction();
	void UpdateWindowSize();
	void RealseAllResources();
	vtkSmartPointer<vtkMatrix4x4> CalculateNewDirectionBasedOnState();
	void InitilizeCorrectionBox(std::vector<std::shared_ptr<IVolume3DRenderer>> volumeViewers,
		std::shared_ptr<misVoreenRepresentation> VolumeRep);
	vtkSmartPointer<vtkMatrix4x4> CalculateNewDirection();
	bool CalculateImageDirection(void);
	bool CalculateFinalTransform(vtkSmartPointer<vtkMatrix4x4> priMatrix, vtkSmartPointer<vtkMatrix4x4> secMatrix);
	void ResetRenderes(void);
	void UpdateRoiInVolume(const double * bnd);
	void UpdateRoiWithWholeImageRoi();
	virtual void UpdateRoi(itk::Object *caller, const itk::EventObject& pEvent);
	void UpdateFaceSettingGUI();
	void FindPackageAutomatic();

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	PointType point;
	double centerPos[3];
	int m_NumberOfConfirmedImages;
	misImageDirectionCalculation*     m_ImageDirecrionCalulation;
	std::shared_ptr<ICorrectionTransformBox> m_BoxWidget;
	IDatasetManager* m_DataSetManger;
	std::shared_ptr<IImage> m_Image;
	misUID    m_imageUID;
	MIS3DInteractionStyle*  m_ImageStyle;
	misBoxObserver * m_BoxObserver;
	misApplicationSetting* m_AppSetting;
	vtkMatrix4x4*  m_ResMatrix;
	vtkMatrix4x4*  m_CorrectionMatrix;
	double m_ROIBound[6];
	std::vector<std::string> m_ROIImagesUID;
	// This is package is use only for internal usage and whouldnot added to misDataSetManger
	std::shared_ptr<ISimpleDataPackage> m_WorkingPackage;
	std::shared_ptr<parcast::IDataCheckingUiUpdater> m_DataCheckingUiUpdater;
	std::shared_ptr<parcast::IVolumeThresholdSliderRangeUpdater> m_ThresholdSliderRangeUpdater;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<parcast::IVolumeMaker> m_VolumeMaker;
	std::shared_ptr<parcast::IVolumeThreshold> m_VolumeThreshold ;
	misROI m_LastActiveROI;

};