#pragma once

#include "IDataBaseCommand.h"
#include "DataAccessException.h"

namespace parcast
{
	class DataBaseCommand : public IDataBaseCommand
	{
	public:
		virtual void SetCommandString(const std::string & command) override;
		virtual std::string GetCommandString() const override;
		virtual void AddParameter(const std::string& paramName, const std::string& lowLevelParameterName, ParameterType type) override;
		virtual void BindParameter(const std::string& paramName, const std::string& paramValue) override;
		virtual void BindParameter(const std::string& paramName, double paramValue) override;
		virtual void BindParameter(const std::string& paramName, long long int paramValue) override;
		virtual void BindParameter(const std::string& paramName, bool paramValue) override;
		virtual void BindParameter(const std::string& paramName, const parcast::DateTime& paramValue) override;
		virtual void BindParameter(const std::string& paramName, std::shared_ptr<ByteArray> paramValue) override;

		using IDataBaseCommand::BindParameter;
		
		virtual BindingCollection GetBindings() const override;
	
	private:
		template<typename T>
		void BindParameterImpl(const std::string& paramName, T paramValue, IDataBaseCommand::ParameterType type)
		{
			auto param = m_Bindings.find(paramName);
			if (param == m_Bindings.end())
				throw DataAccessException("Call to BindParameter with invalid paramName. Parameter not found.");
			if (param->second.Type != type)
				throw DataAccessException("Call to BindParameter with invalid type.");

			param->second.Value = paramValue;
		}

		std::string m_CommandStr;
		BindingCollection m_Bindings;
	};

}
