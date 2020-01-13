#pragma once
#include "misDatabaseIOAbstract.h"


using namespace System;
using namespace System::Data;

class misDatabaseConnectivity : public misDatabaseIOAbstract
{

private:

protected:

public :

	misDatabaseConnectivity(void);

	bool CheckDatabaseConnectivityStatus(void);
	bool AttachPortableDatabase();
	bool DetachPortableDatabase();
};

