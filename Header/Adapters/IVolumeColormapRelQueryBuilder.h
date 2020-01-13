#pragma once

class IVolumeColormapRelQueryBuilder 
{
public:
	virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const = 0;
	virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
	virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() = 0;
}