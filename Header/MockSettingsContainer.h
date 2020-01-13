#pragma once

#include <turtle/mock.hpp>

#include "ISettingsContainer.h"

MOCK_BASE_CLASS(MockSettingsContainer, ISettingsContainer)
{
	MOCK_NON_CONST_METHOD(SetBoolean,    2, void (const std::string& parameterName, bool newValue));
	MOCK_NON_CONST_METHOD(SetInteger,    2, void (const std::string& parameterName, int newValue));
	MOCK_NON_CONST_METHOD(SetDouble,     2, void (const std::string& parameterName, double newValue));
	MOCK_NON_CONST_METHOD(SetString,     2, void (const std::string& parameterName, const std::string& newValue));
	MOCK_NON_CONST_METHOD(SetStringList, 2, void (const std::string& parameterName, const StringList& newValue));

	MOCK_CONST_METHOD(GetBoolean,    1, bool (const std::string& parameterName));
	MOCK_CONST_METHOD(GetInteger,    1, int (const std::string& parameterName));
	MOCK_CONST_METHOD(GetDouble,     1, double (const std::string& parameterName));
	MOCK_CONST_METHOD(GetString,     1, std::string (const std::string& parameterName));
	MOCK_CONST_METHOD(GetStringList, 1, StringList (const std::string& parameterName));
	MOCK_NON_CONST_METHOD(SetValueRange, 2,  void(const std::string& parameterName, const StringList& valueRange));
	MOCK_NON_CONST_METHOD(GetValueRange, 1, StringList(const std::string& parameterName));
	MOCK_CONST_METHOD(IsParamSet, 1, bool (const std::string& parameterName));
	MOCK_CONST_METHOD(GetParamType, 1, ParameterType (const std::string& parameterName));
	MOCK_CONST_METHOD(GetAllSettings, 0, StringList ());

	MOCK_NON_CONST_METHOD(SetParamDescription, 2, void (const std::string& parameterName, const std::string& description));
	MOCK_CONST_METHOD(GetParamDescription, 1, std::string (const std::string& parameterName));

	MOCK_NON_CONST_METHOD(SetParamHumanReadableName, 2, void (const std::string& parameterName, const std::string& humanReadable));
	MOCK_CONST_METHOD(GetParamHumanReadableName, 1, std::string (const std::string& parameterName));

	MOCK_NON_CONST_METHOD(SetParamPopularity, 2, void (const std::string& parameterName, PopularityLevel popularity));
	MOCK_CONST_METHOD(GetParamPopularity, 1, PopularityLevel (const std::string& parameterName));
};