#pragma once

#include "misApplicationSetting.h"
#include "misDataSetManager.h"
#include "misDatabaseUtility.h"
#include "misLogger.h"
#include "misSolutionControl.h"

#ifndef MISDATABASEIOABSTRACT
#define MISDATABASEIOABSTRACT

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Data::SqlTypes;
using namespace System::IO;

class misDatabaseIOAbstract
{
public :
	misDatabaseUtility*     m_DatabaseUtility;
	misDatabaseIOAbstract(void);

protected:
	misLogger*				m_Logger;
	misDatasetManager*      m_DatasetManager;
	misApplicationSetting*  m_ApplicationSetting;	
	misSolutionControl*     m_SolutionControl;
};

#endif