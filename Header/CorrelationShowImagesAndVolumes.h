#pragma once
#include "ICorrelationShowImagesAndVolumes.h"
#include <misColorStruct.h>
#include "INavigationViewersNView.h"
#include "misImageToImageLandmarkBasedRegistration.h"
#include "ICorrelationUpdateViewerLandmarks.h"
#include "IImageCorrelationUiUpdater.h"
#include "ICorrelationSetRegistrationMatrix2Representators.h"
#include "ICorrelationChangeOpacity.h"
#include <misImageCorrelationSetting.h>
#include "IImageCorrelationSettingReader.h"

namespace  parcast
{
	class CorrelationShowImagesAndVolumes :
		public parcast::ICorrelationShowImagesAndVolumes
	{
	public:
		CorrelationShowImagesAndVolumes(std::shared_ptr<misImageToImageLandmarkBasedRegistration>,
		                                std::shared_ptr<INavigationViewersNView>,
		                                std::shared_ptr<parcast::ICorrelationUpdateViewerLandmarks>,
			std::shared_ptr<parcast::IImageCorrelationUiUpdater>,
			std::shared_ptr<ICorrelationSetRegistrationMatrix2Representators>,
			std::shared_ptr<ICorrelationChangeOpacity>, 
			std::shared_ptr<CorrelationRegistrationState>);

		void ShowImagesAndVolumes(std::shared_ptr<ISimpleDataPackage> m_CurrentPackage, std::shared_ptr<IImage> m_FixedImage, std::shared_ptr<IImage> m_MovingImage,const misUID& fixedImageUID, const misUID& movingImageUID,const misColorStruct& fixed, const misColorStruct& moving,
			misOpacityAndUID lastOpacityPack, ViewPortType) override;
		void SetExternalEventViewer(std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> val) final;

		private:

 		void CompleteProcess(itk::Object* caller, const itk::EventObject& pEvent);
		void AddViewerObservers();
		void ManualRegistrationStartUp(std::shared_ptr<IImage> m_FixedImage, std::shared_ptr<IImage> m_MovingImage);
 
		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
		std::shared_ptr<misImageToImageLandmarkBasedRegistration> m_LandmarkBasedFusion;
		std::shared_ptr<parcast::ICorrelationUpdateViewerLandmarks> m_UpdateViewerLandmarks;
		std::shared_ptr<parcast::IImageCorrelationUiUpdater> m_ImageCorrelationUiUpdater;
		std::shared_ptr<ICorrelationSetRegistrationMatrix2Representators> m_RegistrationMatrix2;
		std::shared_ptr<ICorrelationChangeOpacity> m_CorrelationChangeOpacity;
		std::shared_ptr<parcast::IImageCorrelationSettingReader> m_ImageCorrelationSettingReader;
		vtkSmartPointer<vtkMatrix4x4> m_ManualRegistrationTransformMatrix;
		std::shared_ptr<CorrelationRegistrationState> m_CorrelationRegistrationState;
		std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> m_ExternalEventViewer;

 
	};


}
