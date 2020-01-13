#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ICoordinateSystemRepository.h"
#include "misEnums.h"
#include "misSolutionProperty.h"
#include "misTypes.h"

class IDataBaseIO
{
public:
	virtual std::vector<misSolutionProperty> GetAllSolutionsList() = 0;
	virtual bool SaveAllSolutionContent(misSaveSolutionMode savingMode, const misUID& solutionUID) = 0;
	virtual bool ClearDatabaseContent(void) = 0;
	virtual void DeleteSolution(misUID solutionUID) = 0;
	virtual void ReadAllSolutionContent(misUID solutionUID) = 0;

	virtual void SetDataUploadingSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetDataCheckingSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetDataCorrelationSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetAnalysisProcedureSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetCompositeMakingSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetPlanningProcedureSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetLandMarkSelectionSubTabChange(const misUID& solutionUID) = 0;
	virtual void SetLandMarkRegistrationSubTabChange() = 0;

	virtual ~IDataBaseIO() { }
};

