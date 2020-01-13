#pragma once

#pragma warning (push)
#pragma warning (disable : 4503)

struct classcomp {
	bool operator() (const std::string& lhs, const std::string& rhs) const
	{
		size_t first=lhs.find_first_of(" ");
		size_t second=lhs.find_first_of(":");
		std::string temp=lhs.substr(first+1,second-first-1);
		int firstelem=atoi(temp.c_str());
		first=rhs.find_first_of(" ");
		second=rhs.find_first_of(":");
		temp=rhs.substr(first+1,second-first-1);
		int secondelem=atoi(temp.c_str());
		return firstelem<=secondelem;
	}
};

struct SeriAddress
{
	std::string PatientName;
	std::string StudyUID;
	std::string serieUID;

	bool validity;
	SeriAddress(void)
	{
      validity = false;
	  PatientName = "";
	  StudyUID = "";
	  serieUID = "";
	};
};

struct DicomData
{
	std::string PatientName;
	std::string StudyUID;
	std::string seriesDescription;
	std::string studyDescription;
	std::string age;
	std::string gender;
	std::string modality;
	std::string imageName;
	std::string acqDate;
	std::string studyDate;
	DicomData()
	{
	}
};

struct misSerieCheckData
{
	int row;
	int column;
	int numberOfComponent;
	int bitDepth;
};

struct Uid2Description
{
	std::map<std::string, std::string> serie;
	std::map<std::string, std::string> study;
	std::map<std::string, std::string> patient;
};
////////////////////////////////////////////////////////////
typedef std::map<std::string, std::string >                 UIDContainerTypdef;

typedef std::vector<std::string>                SimpleListTypedef;
typedef std::map<std::string,SimpleListTypedef> SeriesType;
typedef std::map<std::string,SeriesType>			StudyType;
typedef std::map<std::string, StudyType >	    PatientsType;

typedef std::map<std::string, SimpleListTypedef       , classcomp>	            SeriesContainerViewingTypdef;
typedef std::map<std::string, SeriesContainerViewingTypdef    , classcomp>	    StudeisContainerViewingTypdef;
typedef std::map<std::string, StudeisContainerViewingTypdef   , classcomp>	    PatientsContainerViewingTypdef;

typedef std::map<std::string,DicomData> SerieUid2Data;

#pragma warning (pop)
