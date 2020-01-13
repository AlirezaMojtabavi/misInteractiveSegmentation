#pragma once
#include "IPanoramicDataDBAdaptor.h"



// The misPanoramicDataSqlDbAdaptor save and retrieve panoramic data to/from SQL Server
class misPanoramicDataSqlDbAdaptor : public IPanoramicDataDBAdaptor
{
public:
	misPanoramicDataSqlDbAdaptor(void);
	~misPanoramicDataSqlDbAdaptor(void);
	virtual bool Save(const misPackagePanormaicData& data);
	virtual bool Load(misPackagePanormaicData& data);
	virtual bool Delete(const std::string& solutionUID);
};

