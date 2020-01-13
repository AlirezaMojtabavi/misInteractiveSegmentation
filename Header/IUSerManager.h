#pragma once

#include "IUserDescription.h"
#include "ISettingsContainer.h"

// The IUserManager class is the abstract interface for Handling User IDs and Load Their Preferences. In this Class we can 
// initialize preferences after loading from user profile directory that was owned by a unique user ID;
class IUserManager
{
public:
	typedef std::vector< std::shared_ptr<IUserDescription> > UserCollection;

	// Switch currently logged on user the one specified by userId. This is called when a user tries to log on to the system.
	virtual void SwitchUser(const std::string& userId) = 0;
	
	// Saves all modified data pertinent to current user (preferences ...) back to corresponding storage spaces. Changes to 
	// current user profile are lost if not saved before current user is logged off.
	virtual void SaveCurrentUserData() = 0;	

	// Get the preferences for the currently logged on user.
	virtual std::shared_ptr<ISettingsContainer> GetCurrentUserPreferences() const = 0;

	// Gets the user currently logged on to the system.
	virtual std::shared_ptr<IUserDescription> GetCurrentUser() const = 0;

	// Get a collection of all the users whose description records have been stored within the user management system.
	virtual UserCollection GetAllUsers() const = 0;

	virtual ~IUserManager(void) { }		
};