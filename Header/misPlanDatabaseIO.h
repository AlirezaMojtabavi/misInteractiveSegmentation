#pragma once

#include "misDatabaseIOAbstract.h"
#include "misSolutionProperty.h"
#include "misVertebraScrewPlanData.h"

#ifndef MISPLANDATABASEIO
#define MISPLANDATABASEIO

using namespace System;
using namespace System::Data;

//Save plan data to database
class misPlanDatabaseIO : public misDatabaseIOAbstract
{

public :

	misPlanDatabaseIO(void);

	bool SetPlanDataListToDB();
	void GetBiopsyPlanDataListFromDB();
	void GetScrewPlanDataListFromDB();
	bool SaveBiopsyPlanDataToDB( std::shared_ptr<misPlanData> biopsyPlanData );
	void SetSolutionProperty( std::shared_ptr<misSolutionProperty> val );
private:

	bool SetPlanDataToDB( std::shared_ptr<misPlanData> planData );
	bool DeletePlanDataListFromDB();	
	bool DeleteScrewPlanDataListFromDB();
	bool DeleteBiopsyPlanFromDB( std::string planDataUID );
	bool SaveScrewPlanDataToDB(misVertebraScrewPlanData* screwPlanData);
	void SetScrewPlanProperties(misVertebraScrewPlanData* planData );
	std::shared_ptr<misSolutionProperty> m_SoutionProperty;

};

#endif