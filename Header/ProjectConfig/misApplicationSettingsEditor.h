#pragma once

#include "misCaptureDevices.h"
#include "misStructTrackingSetting.h"

// The misApplicationSettingsEditor class can be used to load contents of MIS application settings file - an XML file of 
// specific schema. Contents of the file - which are runtime application parameters - can be changed using member variables
// and the contents can be saved back to an XML file.
class misApplicationSettingsEditor
{
public:
	// Loads the contents of the XML specified by the path and parses the application settings and populates member variables.
	void LoadFromFile(const std::string& filePath);

	// Saves the contents of the member variables (application parameters) to the file specified by path. If LoadFromFile has
	// been previously used for loading a file, contents of the file will also be saved (with the exception of those controlled
	// by member variables.
	void SaveToFile(const std::string& filePath);

	std::string m_WorkflowButtonSet;
	misCaptureDevices m_CaptureDevices;
	misStructTrackingSetting m_TrackerSettings;

private:
	// Gets the first child element of the specified element with the specified tag name. An exception is thrown if the 
	// child element does not exist.
	tinyxml2::XMLElement* GetChildElement(tinyxml2::XMLNode* parent, const std::string &childName);

	// Gets the value of the "value" attribute on the element specified by elemName located under the specified parentNode as
	// a string. If the value cannot be retrieved, the defaultValue will be returned.
	std::string GetValueAttributeOnElementAsString(
		tinyxml2::XMLNode* parentNode, const std::string &elemName, const std::string &defaultValue = "");

	// Sets the value of the "value" attribute on the element specified by elemName located under the specified parentNode.
	void SetValueAttributeOnElement(tinyxml2::XMLNode* parentElem, const std::string &elemName, const std::string &newValue);

	// The XMLDocument object is the owner of all XMLElement pointers. Therefore, validity of m_ApplicationSettingsNode relies
	// on it.
	tinyxml2::XMLDocument m_XmlDoc;

	// The XMLElement representing the <ParsissData> / <misApplicationSetting> element in the loaded XML file.
	tinyxml2::XMLElement* m_ApplicationSettingsNode;
};