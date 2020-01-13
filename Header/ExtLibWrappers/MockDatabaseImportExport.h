#pragma once
#include "IDatabaseImportExport.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockDatabaseImportExport, IDatabaseImportExport)
	{
		MOCK_CONST_METHOD(Export, 1, void(const std::string& temporaryDatabasePath));
		MOCK_CONST_METHOD(Import, 1, void(const std::string& temporaryDatabasePath));
	};
}
