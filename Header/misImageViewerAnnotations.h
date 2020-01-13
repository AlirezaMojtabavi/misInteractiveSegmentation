#pragma once
#include "misSideAnnotation.h"
#include "ISideAnnotation.h"
#include "misViewPort.h"
#include "IImageAnnotation.h"

class misImageViewerAnnotations
{
public:
	void UpdateAnnotations(
		std::shared_ptr<IImageAnnotation> imageAnnotation,
	    std::shared_ptr<ISideAnnotation> sideAnnotation,
		std::shared_ptr<parcast::IDentalViewSideAnnotationTextBuilder> annotationBuilder,
		IMAGEORIENTATION orientation,
		misViewPort viewPort,
		int windowWidh,
		int windowHeight,
		double offset,
		int groupIndex,
		bool showAnnoationDetail,
		bool pronState,
		misApplicationType surgeryType,
		bool isOblique,
		bool dentalSpecialViewEnable);


private:

	std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo > GetImageSidesAnotationData();
	std::string BuildAnnotation(misApplicationType surgeryType, IMAGEORIENTATION orientation);
	std::string BuildAnnotationDental(misApplicationType surgeryType, IMAGEORIENTATION orientation, bool oblique, bool withCurve);
	void UpdateImageAnnotation();
	std::shared_ptr<IImageAnnotation> m_ImageAnnotations;
	std::shared_ptr<ISideAnnotation> m_SideAnnotations;
	IMAGEORIENTATION m_Orientation;
	misViewPort m_ViewPort;
	bool m_ShowSideAnnotation;
	double m_Offset;
	int m_WindowWidth;
	int m_WindowHeigh;
	int m_IndexInGroup;
	bool m_ProstrateState;
	misApplicationType m_SurgeryType;
	bool m_IsOblique;
	bool m_DentalSpecialViewEnable;
	std::shared_ptr<parcast::IDentalViewSideAnnotationTextBuilder> m_AnnotationBuilder;
};

