#pragma once

namespace parcast
{

	class IDatabaseImportExport
	{
	public:
		virtual void Export(const std::string& exportedDatabaseFilePath) const = 0;
		virtual void Import(const std::string& importedDatabaseFilePath) const = 0;
	};

}