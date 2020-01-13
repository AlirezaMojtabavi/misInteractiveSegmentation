#pragma once
#include "misResultCode.h"
#include "misEnums.h"
#include "misSolutionProperty.h"

class misGUIEvent;

class IDataBaseManager
{
public:
	virtual std::vector<misSolutionProperty> GetSolutionsList(void) = 0;
	virtual void ReadNewSolution(misUID newSolutionUID) = 0;
	virtual misResultCode::ResultIds SaveSolution(misSaveSolutionMode savingMode, std::string subTabName) = 0;
	virtual void DeleteAllSolutions() = 0;
	virtual void DeleteSolution(misUID solutionUID) = 0;
	virtual bool DistributeEvent(misGUIEvent* pEvent) = 0;
	virtual bool CheckDatabaseValidity(bool forceToCheck = false) = 0;
	virtual void ImportPatient(std::string sourcePath) = 0;
};
