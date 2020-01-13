#include "StdAfx.h"

#include "misException.h"
#include "misTFILoader.h"


misColorListTypedef misTFILoader::LoadTFI(const std::string& fileName) const
{
	// The XMLDocument object is the owner of all XMLElement pointers. Therefore, validity of m_ApplicationSettingsNode
	//relies on it.
	tinyxml2::XMLDocument m_XmlDoc;
	if (m_XmlDoc.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
		throw misException("Failed to load ApplicationSettings XML file. File corrupt or not found.");

	// The first element of XML file should be ParsissData
	auto parsissDataNode = GetChildElement(&m_XmlDoc, "ParsissData");
	auto transFuncIntensityNode = GetChildElement(parsissDataNode, "TransFuncIntensity");
	auto keysNode = GetChildElement(transFuncIntensityNode, "Keys");
	auto lowerThresh = GetAttributeOnElementAsString(transFuncIntensityNode, "lower");
	auto upperThresh = GetAttributeOnElementAsString(transFuncIntensityNode, "upper");

	misColorListTypedef transFuncIntensity;

	for (tinyxml2::XMLElement* keyNode = keysNode->FirstChildElement("key"); 
		keyNode != NULL; keyNode = keyNode->NextSiblingElement("key"))
	{
		auto keyColor = ExtractColorAttributesOfKey (keyNode);
		auto keyIntensity = ExtractIntensityAttributesInKey(keyNode);
		transFuncIntensity[keyIntensity] = keyColor; 
	}
	return transFuncIntensity;
}

tinyxml2::XMLElement* misTFILoader::GetChildElement( tinyxml2::XMLNode* parent, const std::string &childName ) const
{
	auto childElem = parent->FirstChildElement(childName.c_str());
	if (!childElem)
		throw misException(std::string("XML element ") + childName + " not found under node : " + parent->Value());
	return childElem;
}

std::string misTFILoader::GetAttributeOnElementAsString(
	tinyxml2::XMLNode* parentNode, const std::string &elemName, const std::string &attributeName ) const
{
	std::string attribValue;
	auto elem = parentNode->FirstChildElement(elemName.c_str());
	if (!elem)
		return attribValue;
	attribValue = elem->Attribute(attributeName.c_str());
	return attribValue;	
}


float misTFILoader::ExtractIntensityAttributesInKey ( tinyxml2::XMLElement* keyNode ) const
{
	auto intensity = GetAttributeOnElementAsString(keyNode, "intensity");

	return std::stof(intensity);
}

misColorStruct misTFILoader::ExtractColorAttributesOfKey( tinyxml2::XMLElement* keyNode ) const 
{
	auto redColor = GetAttributeOnElementAsString(keyNode, "colorL", "r");
	auto greenColor = GetAttributeOnElementAsString(keyNode, "colorL", "g");
	auto blueColor = GetAttributeOnElementAsString(keyNode, "colorL", "b");
	auto alpha = GetAttributeOnElementAsString(keyNode, "colorL", "a");

	misColorStruct color;
	color.red = std::stoi(redColor);
	color.green = std::stoi(greenColor);
	color.blue = std::stoi(blueColor);
	color.alpha = std::stof(alpha);
	return color;
}
