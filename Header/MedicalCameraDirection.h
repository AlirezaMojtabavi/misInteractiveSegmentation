#pragma once
#include "IMedicalCameraDirection.h"
#include "I3DViewer.h"
namespace parcast
{
	class MedicalCameraDirection :public  IMedicalCameraDirection
	{
	public:
		 MedicalCameraDirection(std::shared_ptr<I3DViewer> _3DViewer);
		~MedicalCameraDirection();

		void SetSupriorView() override;
		void SetInferiorView() override;
		void SetAnteriorView() override;
		void SetPosteriorView() override;
		void SetLeftView() override;
		void SetRightView() override;
		void SetDefaultVeiw() override;
		void SetMainRepresentation(std::shared_ptr<IRepresentation> val) override;

	private:
		std::shared_ptr<I3DViewer> m_3DViewer;
		std::shared_ptr<IRepresentation> m_MainRepresentation;
	};
}

