#pragma once

#include "IDentalImageSliceViewSettings.h"
#include "IDentalViewVector.h"
#include "IImageSliceViewSettings.h"
#include "ISquareQuadCreator.h"

namespace parcast
{

	class DentalImageSliceViewSettings : public IImageSliceViewSettings, public IDentalImageSliceViewSettings
	{
	public:
		DentalImageSliceViewSettings(
			std::shared_ptr<parcast::IDentalViewVector> viewVector, std::shared_ptr<parcast::ISquareQuadCreator> squareCreator);

		// IImageSliceViewSettings interface:
		void SetZoomFactor(double zoomFactor) override;
		const misPlaneAndBoxConfiguration &GetPlaneAndBoxConfig() const override;
		void SetPlaneAndBoxConfig(const misPlaneAndBoxConfiguration &config) override;
		const VectorType &GetPlaneNormalVector() const override;
		void SetProbeDirection(const VectorType &vect) override;
		void SetViewPlaceholder(ViewPlaceholderType val) override;
		ViewPlaceholderType GetViewPlaceholder() const override;
		void SetIsOblique(bool isOblique) override;
		bool IsOblique() const override;
		void SetSurgeryType(misApplicationType appType) override;
		misApplicationType GetSurgeryType() const override;
		VectorType GetViewUpVector() override;
		misQuadGeometry GetImageSliceQuad() override;

		// IDentalImageSliceViewSettings interface:
		void SetPanoramicCoordinateConverter(
			std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter) override;
		void SetDentalSurgeryType(DentalSurgeryType surgeryType) override;

	private:
		ViewVectors GetViewVectors() const;

	public:
		double GetZoomFactor() override;
	private:
		std::shared_ptr<parcast::IDentalViewVector> m_DentalViewVector;
		std::shared_ptr<parcast::ISquareQuadCreator> m_SquareQuadCreator;
		std::shared_ptr<const IPanoramicCoordinatesConverter> m_CoordinateConverter;

		bool m_IsOblique;
		double m_ZoomFactor;
		DentalSurgeryType m_SurgeryType;
		misPlaneAndBoxConfiguration m_PlaneAndBoxConfig;
		ViewPlaceholderType m_ViewPlaceholder;
		itk::Vector<double, 3> m_ProbeDirection;
	};

}