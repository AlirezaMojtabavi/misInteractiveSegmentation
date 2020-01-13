#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "IUSerManager.h"
#include "ISettingsContainer.h"
#include "misApplicationSetting.h"
#include "misLogger.h"
//#include "misDataSetManager.h"
//#include "misSolutionControl.h"
//#include "misVisualizationResourceManager.h"

// The misApplication class which is a singleton throughout the whole MIS application provides the central core to which all
// other global resources are bound. Once the application starts the singular instance misApplication is created. Then the
// misApplication must be initialized. The initialization will, in turn, create and initialize all other global objects in 
// the order dictated by application logic. The misApplication class has accessors for retrieving these global objects.
class misApplication
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<IUserManager> CreateUserManager(const std::string& defaultUserId,
			const std::string& usersRegistryFilePath, const std::string& preferencesFileName) const;
		virtual std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > CreateCorrelationManager() const;
	};

	// Gets the singularly created instance of the class. It creates the instance of not already created.
	static std::shared_ptr<misApplication> GetInstance(std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());

	// Initializes the application by creating other application-wide global objects in the correct order. Before any of 
	// the globals are addressed, Initialize() must be called to ensure their timely construction and initialization.
	void Initialize(const std::string& userID, const std::string& preferencesFileName);

	// Methods providing access to global objects:
	misApplicationSetting* GetApplicationSettings() const;
	//misSolutionControl* GetSolutionController() const;
	//misDatasetManager* GetDatsetManager() const;
	misLogger* GetLogger() const;
	std::shared_ptr<ISettingsContainer> GetCurrentUserPreferences() const;
	std::shared_ptr<IUserManager> GetUserManager() const;

private:
	// Creates an instance of the class and subordinate global objects. It is made private so it can only be created by
	// GetInstance(). 
	misApplication(std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());

	std::shared_ptr<Injector> m_Injector;

	misApplicationSetting* m_ApplicationSettings;
	//misVisualizationResourceManager* m_VisualizationResourceManager;
	misLogger* m_Logger;
	std::shared_ptr<IUserManager> m_UserManager;
};