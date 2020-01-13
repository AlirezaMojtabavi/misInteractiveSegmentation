#pragma once

#include "IDataBaseCommand.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDataBaseCommand, IDataBaseCommand)
	{
		MOCK_NON_CONST_METHOD(SetCommandString, 1, void(const std::string & command));
		MOCK_CONST_METHOD(GetCommandString, 0, std::string());
		MOCK_NON_CONST_METHOD(AddParameter, 3,
			void(const std::string& paramName, const std::string& lowLevelParameterName, ParameterType type));
		MOCK_NON_CONST_METHOD(BindParameter, 2,
			void(const std::string& paramName, const std::string& paramValue), BindParameter_string);
		MOCK_NON_CONST_METHOD(BindParameter, 2, void(const std::string& paramName, double paramValue), BindParameter_double);
		MOCK_NON_CONST_METHOD(BindParameter, 2, void(const std::string& paramName, long long int paramValue), BindParameter_int64);
		MOCK_NON_CONST_METHOD(BindParameter, 2, void(const std::string& paramName, bool paramValue), BindParameter_bool);
		MOCK_NON_CONST_METHOD(BindParameter, 2,
			void(const std::string& paramName, const parcast::DateTime& paramValue), BindParameter_time);
		MOCK_NON_CONST_METHOD(BindParameter, 2,
			void(const std::string& paramName, std::shared_ptr<ByteArray> paramValue), BindParameter_binary);
		MOCK_CONST_METHOD(GetBindings, 0, BindingCollection ());
	};

}
