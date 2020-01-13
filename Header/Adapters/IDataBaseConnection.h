#pragma once

namespace parcast
{

	class IDataBaseCommand;
	class IQueryResult;

	class IDataBaseConnection
	{
	public:
		virtual void Open() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Close() = 0;
		virtual void SetFilePath(const std::string& path) = 0;
		virtual std::shared_ptr<IQueryResult> Exec(std::shared_ptr<const IDataBaseCommand> dbCommand) = 0;

		virtual ~IDataBaseConnection() { }
	};

}