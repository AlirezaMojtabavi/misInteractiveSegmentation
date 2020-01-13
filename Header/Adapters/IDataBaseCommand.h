#pragma once

#include "DateTime.h"

namespace parcast
{
	typedef std::vector<std::uint8_t> ByteArray;

	class IDataBaseCommand
	{
	public:
		enum ParameterType
		{
			Boolean, Integer, Real, String, DateTime, Binary
		};

		typedef boost::variant<
			std::shared_ptr<ByteArray>, bool, long long int, double, std::string, parcast::DateTime> VariantType;

		struct Binding
		{
			ParameterType Type;
			std::string Name;
			std::string LowLevelParameterName;
			VariantType Value;
		};

		typedef std::map<std::string, Binding> BindingCollection;

		virtual void SetCommandString(const std::string& command) = 0;
		virtual std::string GetCommandString() const = 0;
		virtual void AddParameter(const std::string& paramName, const std::string& lowLevelParameterName, ParameterType type) = 0;
		virtual void BindParameter(const std::string& paramName, const std::string& paramValue) = 0;
		virtual void BindParameter(const std::string& paramName, double paramValue) = 0;
		virtual void BindParameter(const std::string& paramName, long long int paramValue) = 0;
		virtual void BindParameter(const std::string& paramName, bool paramValue) = 0;
		virtual void BindParameter(const std::string& paramName, const parcast::DateTime& paramValue) = 0;
		virtual void BindParameter(const std::string& paramName, std::shared_ptr<ByteArray> paramValue) = 0;
		virtual BindingCollection GetBindings() const = 0;

		virtual void BindParameter(const std::string& paramName, int paramValue)
		{
			BindParameter(paramName, static_cast<long long int>(paramValue));
		}

		virtual void BindParameter(const std::string& paramName, unsigned int paramValue)
		{
			BindParameter(paramName, static_cast<long long int>(paramValue));
		}

		virtual void BindParameter(const std::string& paramName, char const * paramValue)
		{
			BindParameter(paramName, std::string(paramValue));
		}

		virtual ~IDataBaseCommand() { }
	};

}
