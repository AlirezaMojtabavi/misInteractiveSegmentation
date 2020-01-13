#pragma once

#include "IDatabaseImportExport.h"

class IDataBaseIO;

namespace parcast
{

	class IDataBaseConnection;
	class IDatabaseInitializer;
	class ISolutionDataAccess;

	class DatabaseImportExport : public IDatabaseImportExport
	{
	public:
		DatabaseImportExport(std::shared_ptr<IDatabaseInitializer> databaseInitializer,
			std::shared_ptr<IDataBaseConnection> dbConnection, std::shared_ptr<IDataBaseIO> dbIo,
			std::shared_ptr<ISolutionDataAccess> solutionDataAccess, const std::string& orginalDbPath);

		virtual void Export(const std::string& exportedDatabaseFilePath) const override;
		virtual void Import(const std::string& importedDatabaseFilePath) const override;

	private:

		class ConnectionTemporaryFilePathSetter
		{
		public:
			ConnectionTemporaryFilePathSetter(
				std::shared_ptr<IDataBaseConnection> dbConnection, const std::string& orginalDbPath,
				const std::string& tempDbPath, std::function<void()> action);

			~ConnectionTemporaryFilePathSetter();

			void operator()();

		private:
			std::function<void()> m_Action;
			std::shared_ptr<IDataBaseConnection> m_DbConn;
			std::string m_OrginalDbPath;
			std::string m_TempDbPath;
		};

		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		std::shared_ptr<IDataBaseIO> m_DatabaseIo;
		std::shared_ptr<IDatabaseInitializer> m_DatabaseInitializer;
		std::shared_ptr<ISolutionDataAccess> m_SolutionDataAccess;

		std::string m_OrginalDbPath;
	};

}
