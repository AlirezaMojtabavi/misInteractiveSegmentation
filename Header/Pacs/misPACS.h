#pragma once
#include "wx\datetime.h"
#include "dicomservers.h"

class misPACS
{
public:
	enum ImageModality
	{
		CT,
		MR,
		All
	};

	struct PacsServerStrct {
		std::string ID;
		std::string AET;
		std::string HostName;
		std::string Port;
	} ;

	struct PatientStrct {
		std::string UID;
		std::string name;
		std::string sex;
		wxString birthDate;
		std::string age;
		std::string description;
		wxString studyDate;
		std::string modality;
		std::vector<IModeloEstudio> studies;
	} ;

	struct StudyStrct {
		std::string UID;
		std::string description;
		std::string acquisitionDate;
		wxString acquisitionTime;
		std::string modality;
	} ;

	struct SeriesStrct {
		std::string UID;
		std::string modality;
		std::string numberOfImages;
	} ;

	bool isMaxNumberOfResultsReached;

	GNC::GCS::Ptr<DicomServer> myServer;
	DicomServerList::TServerList ListOfServers;
	std::vector<PacsServerStrct> pacsServers;
	bool Initialize(bool isFirstTime/*PacsServerStrct& localServer, vector<PacsServerStrct>& pacsServers, int& defaultIndex*/);
	bool ConnectServer(unsigned serverNumber);
	bool ConnectServer(std::string serverID);

	std::vector<PatientStrct> GetListOfPatients(std::string& serverID, ImageModality modality);
	bool SearchPatients(std::string serverID, std::string patientName, std::string patientID, std::string studyUID,
	                    ImageModality modality, std::string dateFrom, std::string dateTo, std::string timeFrom, std::string timeTo, std::vector<PatientStrct>& pacsPatients);
	std::vector<SeriesStrct> GetListOfSeries(std::string studyID);
	std::vector<std::string> GetListOfImages(std::string studyID, std::string seriesID);

	bool Download(const std::string& server, const std::string& modality, const std::string& downloadMode, 
		const std::string& studyUID, const std::string& seriesUID, const std::string& imageUID, bool link);
	std::string currServerID;
	int studyCount;
	PatientStrct currPatient;
	StudyStrct currStudy;
	SeriesStrct currSeries;

	void InsertBullet();

	void CancelProgress();
	void ClosePacs();
	std::string GetTempDirectory();

	misPACS(void);
	~misPACS(void);

private:
	void _FindStudies(std::string& serverID, std::string patientID, std::string patientNumber, std::string accNumber, 
		std::string modalities, std::string fromDate, std::string toDate, std::string fromTime, std::string toTime);
	IModeloDicom _pModelo;
	IModeloDicom::ListaPacientesType _patientList;
	int _CalculateAge(wxDateTime birthDate, wxDateTime studyDate);
};

