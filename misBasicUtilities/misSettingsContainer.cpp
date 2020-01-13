#include "StdAfx.h"
#include "misSettingsContainer.h"

misSettingsContainer::misSettingsContainer(std::shared_ptr<ISettingsContainer> fallBackPreferences)
	: m_FallBackPref(fallBackPreferences)
{
}

void misSettingsContainer::SetBoolean( const std::string& parameterName, bool newValue )
{
	m_Parameters[parameterName].m_Value = newValue;
}

void misSettingsContainer::SetInteger( const std::string& parameterName, int newValue )
{
	m_Parameters[parameterName].m_Value = newValue;
}

void misSettingsContainer::SetDouble( const std::string& parameterName, double newValue )
{
	m_Parameters[parameterName].m_Value = newValue;
}

void misSettingsContainer::SetString( const std::string& parameterName, const std::string& newValue )
{
	m_Parameters[parameterName].m_Value = newValue;
}

void misSettingsContainer::SetStringList( const std::string& parameterName, const StringList& newValue )
{
	m_Parameters[parameterName].m_Value = newValue;
}

bool misSettingsContainer::GetBoolean( const std::string& parameterName ) const
{
	return GetAsType<bool>(parameterName, &ISettingsContainer::GetBoolean);
}

int misSettingsContainer::GetInteger( const std::string& parameterName ) const
{
	return GetAsType<int>(parameterName, &ISettingsContainer::GetInteger);
}

double misSettingsContainer::GetDouble( const std::string& parameterName ) const
{
	return GetAsType<double>(parameterName, &ISettingsContainer::GetDouble);
}

std::string misSettingsContainer::GetString( const std::string& parameterName ) const
{
	return GetAsType<std::string>(parameterName, &ISettingsContainer::GetString);
}

ISettingsContainer::StringList misSettingsContainer::GetStringList( const std::string& parameterName ) const
{
	return GetAsType<StringList>(parameterName, &ISettingsContainer::GetStringList);
}

bool misSettingsContainer::IsParamSet( const std::string& parameterName ) const
{
	auto foundParam = m_Parameters.find(parameterName);
	return foundParam != m_Parameters.cend() && !foundParam->second.m_Value.empty();
}

ISettingsContainer::ParameterType misSettingsContainer::GetParamType( const std::string& parameterName ) const
{
	auto foundParam = m_Parameters.find(parameterName);
	if (foundParam == m_Parameters.cend() || foundParam->second.m_Value.empty())
		return m_FallBackPref ? m_FallBackPref->GetParamType(parameterName) : ISettingsContainer::PT_NOT_SET;

	if(foundParam->second.m_Value.type() == typeid(bool))
		return ISettingsContainer::PT_BOOLEAN;
	else if(foundParam->second.m_Value.type() == typeid(int))
		return ISettingsContainer::PT_INTEGER;
	else if(foundParam->second.m_Value.type() == typeid(double))
		return ISettingsContainer::PT_DOUBLE;
	else if(foundParam->second.m_Value.type() == typeid(std::string))
		return ISettingsContainer::PT_STRING;
	else if(foundParam->second.m_Value.type() == typeid(StringList))
		return ISettingsContainer::PT_STRING_LIST;

	return ISettingsContainer::PT_NOT_SET;
}

ISettingsContainer::StringList misSettingsContainer::GetAllSettings() const
{
	StringList prefNames;
	prefNames.reserve(m_Parameters.size());
	for (auto prefItr = m_Parameters.cbegin(); prefItr != m_Parameters.cend(); ++prefItr)
		prefNames.push_back(prefItr->first);
	return prefNames;
}

std::string misSettingsContainer::GetParamDescription( const std::string& parameterName ) const
{
	auto foundParam = m_Parameters.find(parameterName);
	if (foundParam == m_Parameters.cend() || foundParam->second.m_Description.empty())
		return m_FallBackPref ? m_FallBackPref->GetParamDescription(parameterName) : "";

	return foundParam->second.m_Description;
}

void misSettingsContainer::SetParamDescription( const std::string& parameterName, const std::string& description )
{
	if (!description.empty())
		m_Parameters[parameterName].m_Description = description;
}

std::string misSettingsContainer::GetParamHumanReadableName( const std::string& parameterName ) const
{
	auto foundParam = m_Parameters.find(parameterName);
	if (foundParam == m_Parameters.cend() || foundParam->second.m_HumanReadableName.empty())
		return m_FallBackPref ? m_FallBackPref->GetParamHumanReadableName(parameterName) : "";

	return foundParam->second.m_HumanReadableName;
}

void misSettingsContainer::SetParamHumanReadableName( const std::string& parameterName, const std::string& humanReadable )
{
	if (!humanReadable.empty())
		m_Parameters[parameterName].m_HumanReadableName = humanReadable;
}

ISettingsContainer::PopularityLevel misSettingsContainer::GetParamPopularity( const std::string& parameterName ) const
{
	auto foundParam = m_Parameters.find(parameterName);
	if (foundParam == m_Parameters.cend() || foundParam->second.m_PopularityLevel == PL_NOT_SET)
		return m_FallBackPref ? m_FallBackPref->GetParamPopularity(parameterName) : PL_NOT_SET;

	return foundParam->second.m_PopularityLevel;
}

void misSettingsContainer::SetParamPopularity( const std::string& parameterName, PopularityLevel popularity )
{
	if (popularity != ISettingsContainer::PL_NOT_SET)
		m_Parameters[parameterName].m_PopularityLevel = popularity;
}

void misSettingsContainer::SetValueRange( const std::string& parameterName, const ISettingsContainer::StringList& valueRange )
{
	m_Parameters[parameterName].m_ValueRange = valueRange;
}

ISettingsContainer::StringList misSettingsContainer::GetValueRange( const std::string& parameterName )
{
	return m_Parameters[parameterName].m_ValueRange;
}
