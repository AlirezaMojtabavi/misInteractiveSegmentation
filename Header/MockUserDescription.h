#pragma once

#include <turtle/mock.hpp>

#include "IUserDescription.h"

MOCK_BASE_CLASS(MockUserDescription, IUserDescription)
{
	MOCK_CONST_METHOD(GetUserId, 0, std::string ());
	MOCK_CONST_METHOD(GetProfileDirectoryPath, 0, std::string ());
};