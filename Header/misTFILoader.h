#pragma once

#include "ITFILoader.h"
#include "misColorStruct.h"

class misTFILoader : public ITFILoader
{
public:
	// See ITFILoader
	virtual misColorListTypedef LoadTFI(const std::string& fileName) const override;

private:
	// Extracts intensity and split and other attributes of a key specified by keyNode and Get a transfunction mapping key 
	float ExtractIntensityAttributesInKey ( tinyxml2::XMLElement* keyNode ) const;

	// Extracts color attributes such as RGB and opacity of key specified by keyNode
	misColorStruct ExtractColorAttributesOfKey( tinyxml2::XMLElement* keyNode ) const;

	// Gets child element specified by childName from a parent element
	tinyxml2::XMLElement* GetChildElement( tinyxml2::XMLNode* parent, const std::string &childName ) const;

	// Gets the value of a attribute  specified by attributeName on the element specified by elemName located under the specified
	// parentNode as a string. If the value cannot be retrieved, the defaultValue will be returned.
	std::string GetAttributeOnElementAsString(
		tinyxml2::XMLNode* parentNode, const std::string &elemName, const std::string &attributeName = "value") const;
}; 