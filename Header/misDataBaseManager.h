#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "IDataBaseIO.h"
#include "IDataBaseManager.h"
#include "SolutionImportExport.h"
#include "misDataSetManager.h"
#include "misGuiEvent.h"
#include "misLogger.h"
#include "misObject.h"
#include "misSeconderyNeededHeader.h"
#include "misSolutionProperty.h"
#include "misStrctDataEssantialToExport.h"

class misApplicationSetting;
class misDataBaseIO;
class misTabAndSubTabName;

namespace parcast
{
	class DatabaseInitializer;
	class Clock;
	class PlanCoordSysConverter;
}

class misDataBaseManager :public IDataBaseManager
{
public:
	misDataBaseManager(IDatasetManager * datasetManager,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > coordSysCorrelManager,
		std::shared_ptr<ICoordinateSystemRepository> coordSysRepo);
	~misDataBaseManager();

	std::vector<misSolutionProperty> GetSolutionsList(void) override;
	void ReadNewSolution(misUID newSolutionUID) override;
	misResultCode::ResultIds SaveSolution(misSaveSolutionMode savingMode, std::string subTabName) override;
	void DeleteAllSolutions() override;
	void DeleteSolution(misUID solutionUID) override;
	bool DistributeEvent(misGUIEvent* pEvent) override;

	void ImportPatient(std::string sourcePath) override;

	bool CheckDatabaseValidity(bool forceToCheck = false) override;

private:
	void UpdateSettingFromAppSetting(void);
	void ReadSolution(misUID newSolutionUID);
	void CreateWorld();

	misTabAndSubTabName*	m_TabAndSubTabName;
	misApplicationSetting*	m_AppSetting;
	misLogger*				m_Logger;
	std::vector<misSolutionProperty> m_SolutionsList;
	misApplicationSetting* m_AppSettings;
	IDatasetManager* m_DatasetManager;
	bool m_SaveAllSoltion;

	bool m_UseLegacySqlServer = false;

	std::shared_ptr<IDataBaseIO> m_DataBaseIo;
	std::shared_ptr<parcast::DatabaseInitializer> m_DatabaseInitializer;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<ICoordinateSystemRepository> m_CSRepository;
	std::unique_ptr<parcast::SolutionImportExport> m_SolutionImportExport;
	std::shared_ptr<parcast::Clock> m_Clock;
	std::shared_ptr<parcast::PlanCoordSysConverter> m_PlanToCoordSysConv;

};

