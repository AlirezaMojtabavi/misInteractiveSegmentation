#pragma once
#include "misStrctDicomIO.h"
#include "misImageIndexData.h"
#include "misDataManagerTypes.h"

class misProcessDicomData
{
public:
	misProcessDicomData(DICOMAppHelperModified* appHelper, bool cancelRequest, PatientsType& patients, Uid2Description& uid2Description,
		std::map<std::string, std::string>& imageAddresstoName);
	~misProcessDicomData();
	SeriAddress GetSpecificSeriProperty(misImageIndexData add);
	PatientsContainerViewingTypdef	DataToMap(SerieUid2Data tempDataSerieDCMData);
	imageListTypdef		FindSerie(SeriAddress add);
	misUID	FindSerieUID(misImageIndexData add);
	std::string		GetImageAddress(misImageIndexData add);
private:

	SeriAddress GetSpecificSeriProperty(int patientID, int studyID, int SeriID);
	void PatientImagePositionSort();
	void PatientSliceNumberSort();
	misImageIndexData	GetImageIndex(int patientID, int studyID, int SeriID);

	DICOMAppHelperModified* AppHelper;
	std::map<std::string, std::string>& ImageAddresstoName;
	PatientsType&	m_Patients;
	Uid2Description& m_Uid2Description;
	std::shared_ptr<bool>	m_CancelRequested;
	int		m_SortingMethod;
	std::string		m_DefaultName;
};

