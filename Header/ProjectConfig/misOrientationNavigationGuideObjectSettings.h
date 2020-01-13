#pragma once

#include "misMacros.h"
#include "serializable.h"

// The misOrientationNavigationGideObjectSettings class is a wrapper for the settings used by misOrientationNavigationGideObject
// objects. It is serializable so it can be read from a file and set to the object.
class misOrientationNavigationGuideObjectSettings : public Serializable
{
	// The threshold angle, in degrees, for scaling the guide. Scale of the guide mark is calculated as the ratio of the angle 
	// between plan direction and tool orientation over the threshold.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ThresholdAngle, ThresholdAngle);

	// The minimum scale of the guide mark. The guide mark shrinks linearly with the magnitude of the angle between plan and tool.
	// This minimum keeps the guide mark from shrinking out of sight.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MinimumGuideScale, MinimumGuideScale);

	// The maximum scale of the guide mark. The guide mark grows linearly with the magnitude of the angle between plan and tool.
	// This maximum keeps the guide mark from growing out of convenience.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumGuideScale, MaximumGuideScale);

	// Colour of the guide arrow using R/G/B colour scheme
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_GuideArrowColour, GuideArrowColour);

	// The colour of the caption using R/G/B colour scheme
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_CaptionColour, CaptionColour);

	// The position, in viewport normalized coordinates, of the caption relative to the position of the guide arrow tail point.
	misPrivate2VectorVariableWithPublicAccessorsMacro(double, m_CaptionPosition, CaptionPosition);

	// Sets the size of the caption rectangle in view port normalized measures.
	misPrivate2VectorVariableWithPublicAccessorsMacro(double, m_CaptionSize, CaptionSize);

public:
	misOrientationNavigationGuideObjectSettings(void);
	virtual ~misOrientationNavigationGuideObjectSettings(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );
};

