#pragma once

// The IUserDescription class is the abstract interface for classes that hold essential data for uniquely identifying an 
// application user that at any time might use the system.
class IUserDescription
{
public:
	// The unique identifier of the user across the application using which other application modules might identify the user.
	virtual std::string GetUserId() const = 0;

	// Profile directory path of the user. All uses related data including their preferences is stored in this directory.
	virtual std::string GetProfileDirectoryPath() const = 0;

	virtual ~IUserDescription(void)
	{
	}
};

