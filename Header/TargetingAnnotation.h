#pragma once
#include "misRepresentation.h"
#include <IPilotIndicatorColorSpecifier.h>
#include <Color.h>

namespace parcast
{ 
class TargetingAnnotation :
	public misRepresentation
{
public:
	TargetingAnnotation();
	void SetCaptionText(std::string str) ;
	void SetCaptionColor(IPilotIndicatorColorSpecifier::IndicatorColor color) ;

private:
	vtkSmartPointer<vtkTextActor> m_Caption;
	parcast::Color ConvertIndicatorColorEnum(parcast::IPilotIndicatorColorSpecifier::IndicatorColor color);
	void UpdateCaptionActorColor(vtkSmartPointer<vtkTextActor> actor, parcast::IPilotIndicatorColorSpecifier::IndicatorColor color);
	void SetText(vtkSmartPointer<vtkTextActor> actor, std::string str);
	vtkSmartPointer<vtkTextActor> CreateCaption();
	void InitCaption();

};

}
