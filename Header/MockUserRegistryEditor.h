#pragma once

#include <turtle/mock.hpp>

#include "IUserRegistryEditor.h"

MOCK_BASE_CLASS(MockUserRegistryEditor, IUserRegistryEditor)
{
	MOCK_NON_CONST_METHOD(LoadFromFile, 1, void (const std::string&));
	MOCK_CONST_METHOD(GetUsers, 0, UserCollectionType ());
};
