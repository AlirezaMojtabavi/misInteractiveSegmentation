#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "misDatabaseIOAbstract.h"
#include "misRegistrationResult.h"
#include "misSolutionProperty.h"
#include "misStrctPatientData.h"

using namespace System;
using namespace System::Data;
//The class load and solution and patient property form DB 
class misSolutionInformationDatabaseIO : public misDatabaseIOAbstract
{
public :
	misSolutionInformationDatabaseIO(void);
	std::vector<misSolutionProperty> GetAllSolutionsListFromDB();
	bool SetSolutionInformationToDB(void);
	misSolutionProperty GetSolutionInformationFromDB(misUID soloutionU);
	bool ClearDatabaseContent(void);
	int	 SetPatientInformationToDB(misPatientProperties patientProperty);	
	bool DeleteSolution(misUID solutionUID);
	std::string	FindSolutionFolderPath(misUID solutionUID);
	std::shared_ptr<misSolutionProperty> GetSoloutionProperty() const { return m_SoloutionProperty; }
	void SetSoloutionProperty(std::shared_ptr<misSolutionProperty> val) { m_SoloutionProperty = val; }

private:
	misPatientProperties GetPatientInformationFromDB(misUID soloutionUID);
	std::shared_ptr<misSolutionProperty> m_SoloutionProperty;
};

