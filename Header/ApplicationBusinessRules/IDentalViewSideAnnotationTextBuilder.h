#pragma once

namespace parcast
{

	struct SideAnnotations
	{
		std::string Left;
		std::string Bottom;
		std::string Right;
		std::string Top;
	};

	enum class DentalQuadrant
	{
		UpperRight,
		UpperLeft,
		LowerLeft,
		LowerRight
	};

	enum class ViewerType
	{
		Axial,
		Coronal,
		Sagittal
	};

	class IDentalViewSideAnnotationTextBuilder
	{
	public:
		virtual void SetViewerType(ViewerType viewerType) = 0;
		virtual void SetHasCurve(bool hasCurve) = 0;
		virtual void SetDentalQuadrant(DentalQuadrant quadrant) = 0;
		virtual SideAnnotations GetSideAnnotations() const = 0;

		virtual ~IDentalViewSideAnnotationTextBuilder() = default;
	};

}
