#pragma once

#include "ISettingsContainer.h"

// The misSettingsContainer class provides concrete implementation for ISettingsContainer. It holds reference to another 
// ISettingsContainer object as fall-back when the value of one of its own preference items is requested when it has not been 
// previously set. Therefore, when IsParamSet is false for a certain parameter, the value returned by Get<Type> is that of 
// the Get<Type> from the fall-back preference object. Trying to get a preference item that has not been previously set results 
// in throwing of an exception if a fall-back object is not also present. Attempting to retrieve the value of a parameter using
// a type other than the one used for setting the parameter also results in throwing of an exception.
class misSettingsContainer : public ISettingsContainer
{
public:
	misSettingsContainer(std::shared_ptr<ISettingsContainer> fallBackPreferences = nullptr);

	virtual void SetBoolean( const std::string& parameterName, bool newValue ) override;
	virtual void SetInteger( const std::string& parameterName, int newValue ) override;
	virtual void SetDouble( const std::string& parameterName, double newValue ) override;
	virtual void SetString( const std::string& parameterName, const std::string& newValue ) override;
	virtual void SetStringList( const std::string& parameterName, const StringList& newValue ) override;

	virtual bool GetBoolean( const std::string& parameterName ) const override;
	virtual int GetInteger( const std::string& parameterName ) const override;
	virtual double GetDouble( const std::string& parameterName ) const override;
	virtual std::string GetString( const std::string& parameterName ) const override;
	virtual StringList GetStringList( const std::string& parameterName ) const override;

	virtual bool IsParamSet( const std::string& parameterName ) const override;
	virtual ParameterType GetParamType( const std::string& parameterName ) const override;
	virtual StringList GetAllSettings() const override;

	virtual std::string GetParamDescription( const std::string& parameterName ) const override;
	virtual void SetParamDescription( const std::string& parameterName, const std::string& description ) override;

	virtual std::string GetParamHumanReadableName( const std::string& parameterName ) const override;
	virtual void SetParamHumanReadableName( const std::string& parameterName, const std::string& humanReadable ) override;

	virtual PopularityLevel GetParamPopularity( const std::string& parameterName ) const;
	virtual void SetParamPopularity( const std::string& parameterName, PopularityLevel popularity );
	
	virtual void SetValueRange(const std::string& parameterName, const StringList& valueRange) override;
	virtual StringList GetValueRange(const std::string& parameterName) override;

private:
	// The ParameterDescription is used internally to hold the description and contents of each parameter along with other meta-data
	// related to each parameter.
	struct ParameterDescription
	{
		ParameterDescription() : m_PopularityLevel(PL_NOT_SET) { }
		boost::any m_Value;	// Value of the parameter (including type information)
		StringList m_ValueRange; // All values that the parameter can get
		std::string m_Name;	// Name of the parameter
		std::string m_Description;	// Parameter description
		std::string m_HumanReadableName;
		PopularityLevel m_PopularityLevel;
	};

	// Template method used to retrieve value of a parameter while "any-casting" it to the specified type. It automatically falls
	// back to the fall-back ISettingsContainer by calling and retransmitting the value from the specified Get<Type> method on 
	// the fall-back object if parameter is not set and throws an exception if the fall-back is not present.
	// It also throws exception if the specified type does not match the actual type.
	template <typename Type>
	Type GetAsType(const std::string& paramName, 
		std::function<Type (ISettingsContainer* userPref, const std::string& parameterName)> fallBackMethod) const
	{
		auto foundParam = m_Parameters.find(paramName);
		if (foundParam == m_Parameters.cend())
		{
			if (!m_FallBackPref)
				throw std::exception(
				("Specified preferential parameter not found and no fall-back present. ParamName: " + paramName).c_str());
			auto boundFallBackMethod = std::bind(fallBackMethod, m_FallBackPref.get(), paramName);
			return boundFallBackMethod();
		}
		if (foundParam->second.m_Value.type() != typeid(Type))
		{
			std::ostringstream message;
			message << "Incorrect type specified when querying preference parameter. parameter name: " << paramName << 
				", specified type: " << typeid(Type).name() << ", actual type: " << foundParam->second.m_Value.type().name();
			throw std::exception(message.str().c_str());
		}

		return boost::any_cast<Type>(foundParam->second.m_Value);
	}

	std::shared_ptr<ISettingsContainer> m_FallBackPref;
	std::map<std::string, ParameterDescription> m_Parameters;	// Internal storage for all parameters and their contents

};