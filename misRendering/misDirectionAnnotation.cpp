#include "stdafx.h"
#include "misDirectionAnnotation.h"
using namespace parcast;

misDirectionAnnotation::misDirectionAnnotation(
	std::shared_ptr<parcast::IDentalViewSideAnnotationTextBuilder> annotBuilder) : m_AnnotBuilder(annotBuilder)
{
}

std::map<AnnotationPositionOnWindow, AnnotationInfo >
misDirectionAnnotation::GetAnnotation(IMAGEORIENTATION orientation, bool ProstrateState)
{

	std::map<AnnotationPositionOnWindow, AnnotationInfo > annotationData;
	//CornerMR;//Middle Right

	AnnotationInfo CornerMU;//Middle Up
	AnnotationInfo CornerMD;//Middle Down
	AnnotationInfo CornerML;//Middle Left
	AnnotationInfo CornerMR;//Middle Right

	if (!ProstrateState)//default 
	{
		switch (orientation)
		{
		case AXIAL:

			CornerMU.Text.push_back("A");
			CornerMD.Text.push_back("P");
			CornerML.Text.push_back("R");
			CornerMR.Text.push_back("L");
			break;

		case SAGITTAL:

			CornerMU.Text.push_back("S");
			CornerMD.Text.push_back("I");
			CornerML.Text.push_back("P");
			CornerMR.Text.push_back("A");
			break;

		case CORONAL:

			CornerMU.Text.push_back("S");
			CornerMD.Text.push_back("I");
			CornerML.Text.push_back("R");
			CornerMR.Text.push_back("L");
			break;
		}
	}
	else
	{
		switch (orientation)
		{
		case AXIAL:

			CornerMU.Text.push_back("P");
			CornerMD.Text.push_back("A");
			CornerML.Text.push_back("L");
			CornerMR.Text.push_back("R");
			break;

		case SAGITTAL:

			CornerMU.Text.push_back("S");
			CornerMD.Text.push_back("I");
			CornerML.Text.push_back("A");
			CornerMR.Text.push_back("P");
			break;

		case CORONAL:

			CornerMU.Text.push_back("S");
			CornerMD.Text.push_back("I");
			CornerML.Text.push_back("L");
			CornerMR.Text.push_back("R");
			break;
		}
	}

	annotationData[MiddleUp] = CornerMU;
	annotationData[MiddleDown] = CornerMD;
	annotationData[MiddleLeft] = CornerML;
	annotationData[MiddleRight] = CornerMR;
	return annotationData;
}

std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo> misDirectionAnnotation::GetDentalAnnotations(
	const parcast::ViewerType orientation)
{
	std::map<AnnotationPositionOnWindow, AnnotationInfo> annotationData;
	m_AnnotBuilder->SetViewerType(orientation);
	auto const annots = m_AnnotBuilder->GetSideAnnotations();

	annotationData[MiddleUp].Text.push_back(annots.Top);
	annotationData[MiddleDown].Text.push_back(annots.Bottom);
	annotationData[MiddleRight].Text.push_back(annots.Right);
	annotationData[MiddleLeft].Text.push_back(annots.Left);

	return annotationData;
}
