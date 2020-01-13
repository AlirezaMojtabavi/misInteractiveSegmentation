#pragma once

#include "IUserDescription.h"
#include "IUserManager.h"
#include "IUserRegistryEditor.h"
#include "ISettingStorageEditor.h"

// The misUserManager class handles storage of user description records via user registry editor. It loads current user preferences
// from the preferences file using a preferences editor. Right after construction, this class sets the default user as the 
// currently logged on user and loads its respective preferences. When another user logs on to system (using the SwitchUser 
// function), its preferences are loaded into a new preferences object and the default user preferences are passed, as fall-back, 
// to the current user preferences.
class misUserManager : public IUserManager
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<IUserRegistryEditor> CreateUserRegistryEditor() const;

		virtual std::shared_ptr<ISettingStorageEditor> CreateUserPreferencesEditor(
			std::shared_ptr<ISettingsContainer> preferences) const;

		virtual std::shared_ptr<ISettingsContainer> CreateUserPreferences(
			std::shared_ptr<ISettingsContainer> fallBackPreferences = nullptr) const;
	};

	// Creates and initializes the misUserManager class specifying the default user ID, absolute of relative path to the users
	// registry file, file name to be assumed for preference storages files (only the file name, e.g., Preferences.xml), and an
	// optional dependency injector.
	misUserManager(const std::string& defaultUserId, const std::string& usersRegistryFilePath, 
		const std::string& preferencesFileName, const std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());

	virtual void SwitchUser(const std::string& userId) override;
	virtual void SaveCurrentUserData() override;
	std::shared_ptr<ISettingsContainer> GetCurrentUserPreferences() const override;
	virtual std::shared_ptr<IUserDescription> GetCurrentUser() const override;
	virtual UserCollection GetAllUsers() const override;

private:
	// Search within the collection of all users for a user with the specified ID and get its user description record.
	std::shared_ptr<IUserDescription> FindUser(const std::string& userId) const;

	// Loads the preferences corresponding to currently logged on user (m_CurrentUser), at the same time specifying a fall-back
	// for the created preferences object. Use an empty pointer for fall-back when creating the default preferences.
	std::shared_ptr<ISettingsContainer> LoadCurrentUserPreferences(std::shared_ptr<ISettingsContainer> fallBackPref = nullptr);

	std::shared_ptr<Injector> m_Injector;
	std::shared_ptr<ISettingStorageEditor> m_CurrentUserPrefEditor;	// Used for loading and saving user preferences.
	std::shared_ptr<ISettingsContainer> m_DefaultPreferences;	// Used as fall back for other preference objects
	std::shared_ptr<ISettingsContainer> m_CurrentUserPreferences;	// See GetCurrentUserPreferences
	std::shared_ptr<IUserDescription> m_CurrentUser;	// See GetCurrentUser	
	std::string m_PreferencesFileName;	// See ctor()
	IUserRegistryEditor::UserCollectionType m_AllUsers; // See GetAllUsers
};