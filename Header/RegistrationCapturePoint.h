#pragma once
#include "IRegistrationCapturePoint.h"
#include "RegistrationCaptureLastPosition.h"
#include "misToolFixationAnalysis.h"
#include "IImage.h"
#include "IImageToPatientLandmarkBasedRegistation.h"
#include "IInitialRegistrationResultApplier.h"
#include "ILandmarkRegistrationUIAdapter.h"
#include "ToolRendererManager.h"
#include "IUserMessageBoardManager.h"

namespace parcast
{


	class RegistrationCapturePoint : public IRegistrationCapturePoint
	{
	public:
		RegistrationCapturePoint(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> imageToReferenceRegistration,
			std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager,
			itk::Object::Pointer dummyObject,
			std::shared_ptr<parcast::RegistrationCaptureLastPosition> registrationCaptureLastPosition,
			std::shared_ptr<misToolFixationAnalysis> automaticCapturelandmark,
			std::shared_ptr<parcast::IInitialRegistrationResultApplier> initialRegistrationResultApplier,
			std::shared_ptr<ILandmarkRegistrationUIAdapter> landamrRegUIAdapter,
			std::shared_ptr<parcast::ToolRendererManager> toolRenderersManager,
			double maxError);
		~RegistrationCapturePoint();
		void SetTrackingToolQueruy(std::shared_ptr<ITrackingToolQuery>) override;

		// Inherited via IRegistrationCapturePoint
		virtual int CaptureLastToolPositionAsLandmark(bool checkNewLandmarkMaxErrorForAccepting,
			int currentSelectedLandmarkIndex, bool trackingEnabled, bool lastMustBeSelected) override;
	private:
		std::shared_ptr<parcast::RegistrationCaptureLastPosition> m_RegistrationCaptureLastPosition;
		itk::Object::Pointer m_DummyObject;
		std::shared_ptr<misToolFixationAnalysis> m_AutomaticCapturelandmark;
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		std::shared_ptr<IImage> m_Image;
		std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_ImageToReferenceRegistration;
		std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;
		std::shared_ptr<parcast::IInitialRegistrationResultApplier> m_InitialRegistrationResultApplier;
		std::shared_ptr<ILandmarkRegistrationUIAdapter> m_LandamrRegUIAdapter;
		std::shared_ptr<parcast::ToolRendererManager> m_ToolRenderersManager;
		bool PointIsValid(double* point, int m_CurrentSelectedLandmarkIndex);

		// Inherited via IRegistrationCapturePoint
		virtual void SetImage(std::shared_ptr<IImage> image) override;
		double m_MaxError = 7.0;
	};

}