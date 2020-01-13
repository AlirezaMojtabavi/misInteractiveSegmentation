#pragma once

//A structure to save information of parts of project
//Remind that call SetLogFilePathAndName() before calling SetTestMode()
struct ProjectInfo
{
	std::string m_ProjectName;

	std::string m_FileName;

	std::string m_CallerMethod;

	std::string m_CaleeMethod;

	std::string m_LineNumber;

	void Reset()
	{
		m_ProjectName		= "";
		m_FileName		= "";
		m_CallerMethod    = "";
		m_LineNumber		= "";
		m_CaleeMethod		= "";
	}

};


/*
//	This class is written for testing some important matters in allover the misProjects and also igstk
//	By Mehran Amiri
//*/


class misTestUtility
{
	//name and path of file to be generated
	std::string m_FilePathAndName;

	//The main output stream
	std::ofstream * m_Fout;

	//a flag to determine whether write helping information in file or not
	bool m_TestMode;

	//Writes time and date in file
	void WriteTimeAndDateAsMetaData();
		
public:
	misTestUtility();
	~misTestUtility(void);

	//Sets the flag
	void SetTestMode(bool CurrentMode);

	//returns whether the object of class is in test mode or not
	bool GetStatus(); 

	//Write the info in file
	void WriteInFile(ProjectInfo TestInfo, std::string AdditionalMessage);

	//sets the path and name of log file
	void SetLogFilePathAndName(std::string FileNameAndPath);

	
};

