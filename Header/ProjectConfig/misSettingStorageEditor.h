#pragma once

#include "ISettingStorageEditor.h"

// The misSettingStorageEditor class loads and saves setting storage data from/to XML files. A pointer to the settings object
// object is provided to the editor through its constructor. The same self object is also available through the
// GetPreferences method.
class misSettingStorageEditor : public ISettingStorageEditor
{
public:
	misSettingStorageEditor(std::shared_ptr<ISettingsContainer> preferences);

	// Specifies the absolute path to the node which should be taken as the root for the settings storage. The string path contains
	// names of nested tags separated by a '/' character. For example, passing "ParsissData/UserPreferences" will set the root node
	// the node named "UserPreferences" located under the node named "ParsissData".
	void SetRootNodePath(const std::string& path) override;

	virtual void LoadFromFile(const std::string& preferencesFilePath) override;
	virtual void SaveToFile(const std::string& preferencesFilePath) override;

	virtual std::shared_ptr<ISettingsContainer> GetPreferences() const override;

private:
	// Gets the named XML element as a child of the specified parent node. It creates an XML element with the specified name if 
	// it does not exist.
	tinyxml2::XMLElement* GetOrCreateChildElements(tinyxml2::XMLNode* parentNode, const std::string& nodeName);
	
	// Loads, recursively,  the items under the specified XML node into the ISettingsContainer object and prepends the 
	// specified category prefix to each parameter name. Recursion comes into play when a subnode of the specified node is
	// of value type "Category" or has no value type which defaults to Category. Then, the method is called once more for the 
	// subnode and the name of the subnode used as category prefix.
	void LoadPreferenceItemsUnderNode(tinyxml2::XMLNode* parentNode, const std::string& categoryPrefix);

	std::shared_ptr<ISettingsContainer> m_SettingsContainer;	// See GetPreferences

	// The XMLDocument object is the owner of all XMLElement pointers. Therefore, validity of m_UsersNode relies on it.
	tinyxml2::XMLDocument m_XmlDoc;

	std::string m_RootNodePath;	// See SetRootNodePath
};