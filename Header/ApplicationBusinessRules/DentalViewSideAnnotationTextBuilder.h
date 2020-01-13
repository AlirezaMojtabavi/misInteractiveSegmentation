#pragma once
#include "IDentalViewSideAnnotationTextBuilder.h"

namespace parcast
{

	class DentalViewSideAnnotationTextBuilder : public IDentalViewSideAnnotationTextBuilder
	{
	public:
		DentalViewSideAnnotationTextBuilder();

		void SetViewerType(ViewerType viewerType) override;
		void SetHasCurve(bool hasCurve) override;
		void SetDentalQuadrant(DentalQuadrant quadrant) override;
		SideAnnotations GetSideAnnotations() const override;

	private:
		using HasCurveType = bool;
		using MapIndexType = std::tuple<HasCurveType, DentalQuadrant, ViewerType>;
		using MapType = std::map<MapIndexType, SideAnnotations>;

		ViewerType m_ViewerType{};
		HasCurveType m_HasCurve{};
		DentalQuadrant m_Quadrant{};

		const MapType Annotations;
	};

}
