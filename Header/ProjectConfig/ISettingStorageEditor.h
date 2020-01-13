#pragma once

#include "ISettingsContainer.h"

// The ISettingStorageEditor class provides an abstract interface for opening, editing, and saving a settings storage file.
class ISettingStorageEditor
{
public:
	// Loads the user preferences from the file specified.
	virtual void LoadFromFile(const std::string& preferences) = 0;

	// Saves the user preferences to the file specified.
	virtual void SaveToFile(const std::string& preferences) = 0;

	// Gets the Preferences loaded from the registry.
	virtual std::shared_ptr<ISettingsContainer> GetPreferences() const = 0;

	virtual void SetRootNodePath(const std::string& path) = 0;

	virtual ~ISettingStorageEditor(void) { }
};

