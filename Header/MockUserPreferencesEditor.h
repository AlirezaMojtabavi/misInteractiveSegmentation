#pragma once

#include <turtle/mock.hpp>

#include "ISettingStorageEditor.h"

MOCK_BASE_CLASS(MockUserPreferencesEditor, ISettingStorageEditor)
{
	MOCK_NON_CONST_METHOD(LoadFromFile, 1, void (const std::string& preferences));
	MOCK_NON_CONST_METHOD(SaveToFile, 1, void (const std::string& preferences));
	MOCK_CONST_METHOD(GetPreferences, 0, std::shared_ptr<ISettingsContainer>());
	MOCK_NON_CONST_METHOD(SetRootNodePath, 1, void(const std::string& path));
};