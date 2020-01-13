#pragma once

#include "misMacros.h"
#include "serializable.h"

class misPlanAxisNavigationGuideObjectProperties : public Serializable
{
	// The threshold distance, in degrees, for scaling the guide. Distances greater than or equal to this will identically scale 
	// the guide, while smaller angles scale down the guide to the tool tip to start point distance and the threshold angle.
	misPrivateVariableWithPublicAccessorsMacro(double, m_ThresholdDistance, ThresholdDistance);

	// The minimum scale of the guide mark. The guide mark shrinks linearly with the decreasing distance between tool tip and the
	// plan start point. This minimum keeps the guide mark from shrinking out of sight.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MinimumGuideScale, MinimumGuideScale);

	// The maximum scale of the guide mark. The guide mark grows linearly with the increasing distance between tool tip and the
	// plan start point. This maximum keeps the guide mark from growing out of convenience.
	misPrivateVariableWithPublicAccessorsMacro(double, m_MaximumGuideScale, MaximumGuideScale);

	// Colour of the guide arrow using R/G/B colour scheme
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_GuideArrowColour, GuideArrowColour);

	// The colour of the caption using R/G/B colour scheme
	misPrivate3VectorVariableWithPublicAccessorsMacro(double, m_CaptionColour, CaptionColour);

	// The position, in normalized viewport coordinates, of the caption relative to the position of the guide arrow tail point.
	misPrivate2VectorVariableWithPublicAccessorsMacro(double, m_CaptionPosition, CaptionPosition);

	// Sets the size of the caption rectangle in view port normalized measures.
	misPrivate2VectorVariableWithPublicAccessorsMacro(double, m_CaptionSize, CaptionSize);

public:
	misPlanAxisNavigationGuideObjectProperties(void);

	virtual void serialize( XmlSerializer& s ) const;

	virtual void deserialize( XmlDeserializer& s );

};

