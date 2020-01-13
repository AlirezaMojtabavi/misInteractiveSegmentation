#pragma once
#include "VisualizationGeneralTypes.h"
#include "IDentalViewSideAnnotationTextBuilder.h"


namespace parcast
{
	enum AnnotationPositionOnWindow { LeftDown, LeftUp, RightDown, RightUp, MiddleUp, MiddleDown, MiddleRight, MiddleLeft };

	struct FontColor {

		double Red;
		double Green;
		double Blue;
	};

	struct misFontSize {
		double Font;
	};

	struct AnnotationInfo {

		std::vector<std::string> Text;
		std::vector<FontColor>   FontColor;
		std::vector<misFontSize> FontSize;
	};


	class misDirectionAnnotation
	{
	public:
		misDirectionAnnotation() = default;
		explicit misDirectionAnnotation(std::shared_ptr<parcast::IDentalViewSideAnnotationTextBuilder> annotBuilder);

		std::map<AnnotationPositionOnWindow, AnnotationInfo >  GetAnnotation(IMAGEORIENTATION  orientation, bool prostrateState);
		std::map<AnnotationPositionOnWindow, AnnotationInfo> GetDentalAnnotations(const parcast::ViewerType orientation);;

	private:
		std::shared_ptr<IDentalViewSideAnnotationTextBuilder> m_AnnotBuilder;
	};
}






