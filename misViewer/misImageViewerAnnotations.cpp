#include "stdafx.h"
#include "..\Header\misImageViewerAnnotations.h"
#include "misPlanarRepresentation.h"
#include "misEnumUtilities.h"



void misImageViewerAnnotations::UpdateAnnotations(
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
	bool dentalSpecialViewEnable)
{
	m_ImageAnnotations = imageAnnotation;
	m_SideAnnotations = sideAnnotation;
	m_Orientation = orientation;
	m_ViewPort = viewPort;
	m_ShowSideAnnotation = showAnnoationDetail;
	m_Offset = offset;
	m_WindowWidth = windowWidh;
	m_WindowHeigh = windowHeight;
	m_IndexInGroup = groupIndex;
	m_ProstrateState = pronState;
	m_SurgeryType = surgeryType;
	m_IsOblique = isOblique;
	m_DentalSpecialViewEnable = dentalSpecialViewEnable;
	m_AnnotationBuilder  = annotationBuilder;
	UpdateImageAnnotation();
}


void misImageViewerAnnotations::UpdateImageAnnotation()
{

	m_ImageAnnotations->SetRenWinSize(static_cast<int> (m_ViewPort.Width() * m_WindowWidth),
		static_cast<int> (m_ViewPort.Height() * m_WindowHeigh));
	//add distance annotation for splitted viewers		
	if (m_ViewPort.Width() != 1 && m_ViewPort.Height() != 1)
	{
		if(m_Offset)
			m_ImageAnnotations->AddDistanceAnnotaion(m_Offset);
		else
			m_ImageAnnotations->AddDistanceAnnotaion(0);
	}
	std::string anotationStr = BuildAnnotation(m_SurgeryType, m_Orientation);
	if (m_IndexInGroup == 0)
		m_ImageAnnotations->SetTitle(anotationStr);
	if (m_ShowSideAnnotation)
	{

		auto annotationData = GetImageSidesAnotationData();
		m_SideAnnotations->SetSideAnnotation(annotationData);

	}

	m_SideAnnotations->SetRenWinSize(static_cast<int> (m_ViewPort.Width() * m_WindowWidth),
		static_cast<int> (m_ViewPort.Height() * m_WindowHeigh));
}

std::string misImageViewerAnnotations::BuildAnnotation(misApplicationType surgeryType, IMAGEORIENTATION orientation) 
{
	if (surgeryType == Dental)
		return BuildAnnotationDental(surgeryType, orientation, m_IsOblique, m_DentalSpecialViewEnable);
	return misEnumUtilities::ConvertImageOrientationTypeEnumToString(orientation, m_IsOblique);
}

std::string misImageViewerAnnotations::BuildAnnotationDental(misApplicationType surgeryType, 
	IMAGEORIENTATION orientation, bool oblique, bool withCurve) 
{
	if (m_DentalSpecialViewEnable)
	{
		if (m_IsOblique)
		{
			switch (orientation)
			{
			case AXIAL:
				return "Inline Occlusal";
			case CORONAL:
				return "Inline Mesiodistal";
			case SAGITTAL:
				return "Inline Buccolingual";
			}
		}
		else
		{
			switch (orientation)
			{
			case AXIAL:
				return "Occlusal";
			case CORONAL:
				return "Mesiodistal";
			case SAGITTAL:
				return "Buccolingual";
			}
		}
	}
	else
	{
		if (m_IsOblique)
		{
			switch (orientation)
			{
			case AXIAL:
				return "Inline Axial";
			case CORONAL:
				return "Inline Coronal";
			case SAGITTAL:
				return "Inline Sagittal";
			}
		}
		else
		{
			switch (orientation)
			{
			case AXIAL:
				return "Axial";
			case CORONAL:
				return "Coronal";
			case SAGITTAL:
				return "Sagittal";
			}
		}
	}
	return "Unknown orientation!";
}

std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo >  
misImageViewerAnnotations::GetImageSidesAnotationData()
{
	if (m_SurgeryType == Dental)
	{
		auto annotationBuilder = parcast::misDirectionAnnotation(m_AnnotationBuilder);

		auto viewerTypeMap = std::map<IMAGEORIENTATION, parcast::ViewerType>{
			{AXIAL, parcast::ViewerType::Axial},
			{ SAGITTAL, parcast::ViewerType::Sagittal },
			{ CORONAL, parcast::ViewerType::Coronal } };

		return annotationBuilder.GetDentalAnnotations(viewerTypeMap[m_Orientation]);
	}

	auto annotationBuilder = parcast::misDirectionAnnotation();
	return annotationBuilder.GetAnnotation(m_Orientation, m_ProstrateState);

}
