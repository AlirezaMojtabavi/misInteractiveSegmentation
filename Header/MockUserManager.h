#pragma once

#include <turtle/mock.hpp>

#include "IUSerManager.h"

MOCK_BASE_CLASS(MockUserManager, IUserManager)
{
	MOCK_NON_CONST_METHOD(SwitchUser, 1, void (const std::string&) );
	MOCK_CONST_METHOD(GetCurrentUserPreferences, 0, std::shared_ptr<ISettingsContainer>());
	MOCK_CONST_METHOD(GetCurrentUser, 0, std::shared_ptr<IUserDescription> GetCurrentUser());
	MOCK_CONST_METHOD(GetAllUsers, 0, UserCollection ());
		
};