#pragma once

#include "IUserDescription.h"

// The IUserRegistryEditor class provides an abstract interface for opening, editing, and saving a MIS user registry XML file.
// The interface has not been completely designed yet. Other functionalities including adding, removing, modifying users might
// be added later.
class IUserRegistryEditor
{
public:
	typedef std::vector< std::shared_ptr<IUserDescription> > UserCollectionType;

	// Loads the user registry from the XML file specified.
	virtual void LoadFromFile(const std::string& registryFilePath) = 0;

	// Gets the list of users loaded from the registry.
	virtual UserCollectionType GetUsers() const = 0;

	virtual ~IUserRegistryEditor(void) { }
};

