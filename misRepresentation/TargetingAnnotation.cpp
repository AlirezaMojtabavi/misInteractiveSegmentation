#include "stdafx.h"
#include "..\Header\TargetingAnnotation.h"
#include <Color.h>


parcast::TargetingAnnotation::TargetingAnnotation():
misRepresentation("Targeting Annotation")
{
	InitCaption();
}

void parcast::TargetingAnnotation::SetCaptionText(std::string str)
{
	if (m_Caption.GetPointer())
	{
		std::ostringstream depthFormatterStream;
		depthFormatterStream << str;
		std::string captionString = depthFormatterStream.str();
		m_Caption->SetInput(captionString.c_str());
	}
}

void parcast::TargetingAnnotation::SetCaptionColor(parcast::IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	if (m_Caption.GetPointer())
	{
		UpdateCaptionActorColor(m_Caption, color);
	}

}

vtkSmartPointer<vtkTextActor> parcast::TargetingAnnotation::CreateCaption()
{
	auto caption = vtkSmartPointer<vtkTextActor>::New();
	caption->SetTextScaleModeToNone();
	caption->SetDisplayPosition(20, 20);
	caption->SetNonLinearFontScale(25, 25);
	m_Actors.push_back(caption);
	return caption;
}

void parcast::TargetingAnnotation::SetText(vtkSmartPointer<vtkTextActor> actor, std::string str)
{
	std::ostringstream depthFormatterStream;
	depthFormatterStream << str;
	std::string captionString = depthFormatterStream.str();
	actor->SetInput(captionString.c_str());
}

void parcast::TargetingAnnotation::UpdateCaptionActorColor(vtkSmartPointer<vtkTextActor> actor,
                                              parcast::IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	if (color == parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Black)
	{
		actor->SetVisibility(false);
		return;
	}

	actor->SetVisibility(true);
	auto rgbColor = ConvertIndicatorColorEnum(color).GetNormRgb();
	actor->GetProperty()->SetColor(std::get<0>(rgbColor), std::get<1>(rgbColor), std::get<2>(rgbColor));
}

parcast::Color parcast::TargetingAnnotation::ConvertIndicatorColorEnum(parcast::IPilotIndicatorColorSpecifier::IndicatorColor color)
{
	switch (color)
	{
	case parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Gray:
	{
		return parcast::Color::FromRgb(127, 127, 127);
	}
	case parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Green:
	{
		return parcast::Color::FromRgb(0, 255, 0);
	}
	case parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Red:
	{
		return parcast::Color::FromRgb(255, 0, 0);
	}
	case parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Yellow:
	{
		return parcast::Color::FromRgb(255, 255, 0);
	}
	case parcast::IPilotIndicatorColorSpecifier::IndicatorColor::Black:
	{
		return parcast::Color::FromRgb(0, 0, 0);
	}
	}
}


void parcast::TargetingAnnotation::InitCaption()
{
 
		m_Caption = CreateCaption();
		UpdateCaptionActorColor(m_Caption, IPilotIndicatorColorSpecifier::IndicatorColor::Green);
		m_Caption->SetPosition(0.5, 0.5);
 
}