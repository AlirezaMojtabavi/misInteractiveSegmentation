#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ISettingsContainer.h"
#include "misDataBaseManager.h"
#include "misDataSetManager.h"
#include "misEntApplicationWorkflow.h"
#include "misEventMacros.h"

// The misEntApplication class holds all the data, structures, and business workflow related to an MIS ENT application. The
// misEntApplication does not provide an application loop of its own. Therefore, the UI (or other supervising application 
// loop) should call the UpdateStatus() method regularly to enable flow of the application. 
class misEntApplication
{
public:
	MIS_HAS_EVENTS_IMPLEMENTATION_WITHOUT_BASE;

	enum Status
	{
		// The application object has not been fully constructed yet
		NotConstructed,

		// Construction of the application object is completed, but it has not been initialized. The first call to UpdateStatus
		// will trigger initialization.
		NotInitialized,

		// Initialization of the application has started but not finished yet.
		Initializing,

		// The application has completed its initialization step and subsequent calls to UpdateStatus will execute the 
		// application cycle by updating the status of all the subordinate objects.
		Running,

		// Signifies that an application exit has been demanded. Calling UpdateStatus in this status has no effect and the 
		// superordinate object (initiator of the application loop) must terminate the loop.
		Exit
	};

	MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(CurrentStatusChanged, Status lastStatus, Status currentStatus);

	// Pass the application command line arguments. The misEntApplication constructor will use them to initialize the application.
	misEntApplication(int argc, char* argv[]);

	// Causes the internal state of all the application subsystems to be updated.
	void UpdateStatus();

	Status GetCurrentStatus() const;

	// Gets the global application settings which also includes sections related to the UI.
	std::shared_ptr<ISettingsContainer> GetApplicationSettings() const;
	
	// Gets the application business workflow (ENT workflow). Calls to UpdateStatus() are automatically propagated to the workflow.
	// The UI will communicate with the workflow object and the workflow steps directly.
	std::shared_ptr<misEntApplicationWorkflow> GetApplicationWorkflow() const;

	// Gets the version string for this application build.
	std::string GetVersionString() const;

private:
	// Performs initialization steps of the application
	void Initialize();

	// Changes the current status of the application object and raises the CurrentStatusChanged signal accordingly.
	void ChangeStatus(Status newStatus);

	char ** m_ArgV;
	int m_ArgC;

	Status m_Status;
	std::string m_ApplicationSettingsFilePath;
	std::shared_ptr<ISettingsContainer> m_ApplicationSettings;
	std::shared_ptr<misEntApplicationWorkflow> m_Workflow;
	std::shared_ptr< ICoordinateSystemRepository > m_CoordSysRepo;
	std::shared_ptr<  ICoordinateSystemCorrelationManager<std::string>  > m_CorrelationManager;
	misDatasetManager* m_DatasetManager;
	std::shared_ptr<misDataBaseManager> m_DatabaseManager;
	std::string m_VersionString;
	// misSolutionControl* m_SolutionController;
	// m_Tracking;
	// m_DataAccess;
};