#pragma once

#include "IUserDescription.h"

class misUserDescription : public IUserDescription
{
public:
	misUserDescription(const std::string& userId, const std::string& profileDirPath);

	virtual std::string GetUserId() const;

	virtual std::string GetProfileDirectoryPath() const;

private:
	std::string m_UserId;
	std::string m_ProfileDirectoryPath;
};

