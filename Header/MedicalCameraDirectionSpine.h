#pragma once
#include "IMedicalCameraDirection.h"
#include "I3DViewer.h"

namespace parcast
{
	class MedicalCameraDirectionSpine :public IMedicalCameraDirection
	{
	public:
		MedicalCameraDirectionSpine(std::shared_ptr<I3DViewer> _3DViewer);

		void SetDefaultVeiw() final;
		void SetLeftView() final;
		void SetRightView() final;
		void SetSupriorView() override;
		void SetInferiorView() override;
		void SetAnteriorView() override;
		void SetPosteriorView() override;
		void SetMainRepresentation(std::shared_ptr<IRepresentation> val) override;
	private:
		std::shared_ptr<I3DViewer> m_3DViewer;
		std::shared_ptr<IRepresentation> m_MainRepresentation;
	};
}

