#pragma once

struct  misStrctDataEssantialToExport
{
	std::string m_DestinationPath;
	std::string m_SolutionUID;
	std::string m_MainDataPath;

	void Reset()
	{
		m_DestinationPath = "";
		m_MainDataPath = "";
		m_SolutionUID = "";
	}

	misStrctDataEssantialToExport()
	{
		this->Reset();
	}
};
