#pragma once

#include "IDataBaseIO.h"

MOCK_BASE_CLASS(MockDataBaseIO, IDataBaseIO)
{
	MOCK_NON_CONST_METHOD(SetSolutionProperty, 1, void(std::shared_ptr<misSolutionProperty> val));
	MOCK_NON_CONST_METHOD(SetCScorrelationManager, 1, void(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val));
	MOCK_NON_CONST_METHOD(SetCoordinateSystemRepository, 1, void(std::shared_ptr<ICoordinateSystemRepository> val));
	MOCK_NON_CONST_METHOD(GetAllSolutionsList, 0, std::vector<misSolutionProperty>());
	MOCK_NON_CONST_METHOD(SaveAllSolutionContent, 2, bool(misSaveSolutionMode savingMode, const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(ClearDatabaseContent, 0, bool());
	MOCK_NON_CONST_METHOD(DeleteSolution, 1, void(misUID solutionUID));
	MOCK_NON_CONST_METHOD(ReadAllSolutionContent, 1, void(misUID solutionUID));
	MOCK_NON_CONST_METHOD(FindSolutionFolderPath, 1, std::string(misUID solutionUID));
	MOCK_NON_CONST_METHOD(SetDataUploadingSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetDataCheckingSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetDataCorrelationSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetAnalysisProcedureSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetCompositeMakingSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetPlanningProcedureSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetLandMarkSelectionSubTabChange, 1, void(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(SetLandMarkRegistrationSubTabChange, 0, void());
	MOCK_NON_CONST_METHOD(CheckDatabaseConnectivityStatus, 0, bool());
	MOCK_NON_CONST_METHOD(PreparePortableDatabaseToExport, 1, bool(const misUID& solutionUID));
	MOCK_NON_CONST_METHOD(PreparePortableDatabaseToImport, 0, bool());
	MOCK_NON_CONST_METHOD(PreparePortableDatabaseToReadImportedSolution, 0, bool());
	MOCK_NON_CONST_METHOD(UpdateMainDatabase, 1, bool(const misUID& solutionUID));

};
