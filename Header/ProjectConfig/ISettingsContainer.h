#pragma once

// The ISettingsContainer class is the abstract interface to classes that can hold setting parameters as name-value pairs. It
// can also be used to hold application default or general preferences. Each parameter is uniquely identified and referenced by 
// its parameter name. Possible operations for each parameter are setting and getting its value with any of the allowed data 
// types, getting and setting parameter metadata (description, human readable name, data type) and whether it has been set at
// least once.
class ISettingsContainer
{
public:
	// Determines the data type of a preference item
	enum ParameterType
	{
		PT_BOOLEAN,
		PT_INTEGER,
		PT_DOUBLE,
		PT_STRING,
		PT_STRING_LIST,
		PT_NOT_SET
	};

	// Determines the popularity level for a parameter.
	enum PopularityLevel
	{
		PL_NOT_SET = 0,
		PL_VERY_UNPOPULAR,
		PL_UNPOPULAR,
		PL_MEDIUM_POPULARITY,
		PL_POPULAR,
		PL_VERY_POPULAR
	};

	typedef std::vector<std::string> StringList;	// Corresponds to PT_STRING_LIST

	// Using the following methods, you can set the named parameter with the specified new value which might be of any of the
	// allowed data types.
	virtual void SetBoolean(const std::string& parameterName, bool newValue) = 0;
	virtual void SetInteger(const std::string& parameterName, int newValue) = 0;
	virtual void SetDouble(const std::string& parameterName, double newValue) = 0;
	virtual void SetString(const std::string& parameterName, const std::string& newValue) = 0;
	virtual void SetStringList(const std::string& parameterName, const StringList& newValue) = 0;

	// Using the following methods, you can get the named parameter value as any of the allowed data types. Make sure to check 
	// whether the named parameter is set and that it has the correct data type before retrieving the value. Errors might occur 
	// if you attempt to retrieve value of a parameter with a different type than the one with which it has been set or if the
	// parameter with the specified name has not been set at all. See GetParamType, IsParamSet
	virtual bool GetBoolean(const std::string& parameterName) const = 0;
	virtual int GetInteger(const std::string& parameterName) const = 0;
	virtual double GetDouble(const std::string& parameterName) const = 0;
	virtual std::string GetString(const std::string& parameterName) const = 0;
	virtual StringList GetStringList(const std::string& parameterName) const = 0;

	// Determines whether the parameter of the specified name has been set (at least once) using any of the Set* methods.
	virtual bool IsParamSet(const std::string& parameterName) const = 0;

	// Gets the data type of the named parameter.
	virtual ParameterType GetParamType(const std::string& parameterName) const = 0;

	// Gets a list containing the names of all the preferences that have been introduced to this object. Note that this does not
	// necessarily mean that all these preferences have their values set as some of them might have been introduced through setting
	// a description or human readable name for them. Therefore make sure to use IsParamSet before trying to get the value of each.
	virtual StringList GetAllSettings() const = 0;

	// Gets/sets a short description for the specified parameter name. This description could be used to inform the user of the
	// significance of the parameter, when and how to change it, possible values, etc. An empty string means the description 
	// has not been set.
	virtual std::string GetParamDescription(const std::string& parameterName) const = 0;
	virtual void SetParamDescription(const std::string& parameterName, const std::string& description) = 0;
	
	virtual void SetValueRange(const std::string& parameterName, const StringList& valueRange) = 0;
	virtual StringList GetValueRange(const std::string& parameterName) = 0;

	// Gets/sets a human readable for the specified parameter name. An empty string means the description has not been set. This
	// name can be used as a label in user interface applications.
	virtual std::string GetParamHumanReadableName(const std::string& parameterName) const = 0;
	virtual void SetParamHumanReadableName(const std::string& parameterName, const std::string& humanReadable) = 0;

	// Gets/sets the popularity level of the specified parameter. The popularity level of a parameter can be used to decide whether
	// it should be displayed in a certain setting editor based on application, user permissions and expertise, user's choice
	// whether to see only the most popular settings...
	virtual PopularityLevel GetParamPopularity(const std::string& parameterName) const = 0;
	virtual void SetParamPopularity(const std::string& parameterName, PopularityLevel popularity) = 0;

	virtual ~ISettingsContainer() {}
};