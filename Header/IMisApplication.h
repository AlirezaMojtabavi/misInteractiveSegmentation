#pragma once

// which is a singleton throughout the whole MIS application provides the central core to which all
// other global resources are bound. Once the application starts the singular instance misApplication is created. Then the
// misApplication must be initialized. The initialization will, in turn, create and initialize all other global objects in 
// the order dictated by application logic. The misApplication class has accessors for retrieving these global objects.
class IMisApplication
{
public:
	// Initializes the application by creating other application-wide global objects in the correct order. Before any of 
	// the globals are addressed, Initialize() must be called to ensure their timely construction and initialization.
	virtual void Initialize() = 0;

	// Methods providing access to global objects:
	virtual misApplicationSetting* GetApplicationSettings() const = 0;
	virtual misLogger* GetLogger() const = 0;
	virtual std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > GetCorrelationManager() const = 0;
	virtual std::shared_ptr<ISettingsContainer> GetCurrentUserPreferences() const = 0;
	virtual std::shared_ptr<IUserManager> GetUserManager() const = 0;

	virtual ~IMisApplication(void) { }
};

