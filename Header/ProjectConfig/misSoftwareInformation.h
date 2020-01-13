#pragma once

#include "misLicenseStrct.h"

class misSoftwareInformation
{
public:
	misSoftwareInformation(std::string vrsion);
	void SetLicensedTo(const std::string&);
	void SetVersion(const std::string&);
	void SetLiFileName(const std::string&);
	std::string GetVersion() const;
	std::string GetLicensedTo() const;
	std::string GetCopyRight() const;
	std::string GetLiFileName() const;
	std::string GetProductName() const;
	std::string GetWebsite() const;
	std::string GetReLiKe() const;
	misUserLicenseStrct GetUserAppData() const;
	void SetUserAppData(const misUserLicenseStrct& data);
	void SetReLiKe(const std::string& relike);

private:
	std::string m_Version;
	std::string m_LicensedTo;
	std::string m_CopyRight;
	std::string m_Website;
	std::string m_ProductName;
	std::string m_LiFileName;
	std::string m_ReLiKe;
	misUserLicenseStrct  m_UserAppData; 

};
 