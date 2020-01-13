#pragma  once

#include "misEnums.h"

typedef std::string misUID;

namespace parcast
{
	class Clock;
	class DateTime;
	class DateTimeOperation;
}

struct misPatientProperties
{
	misPatientProperties();
	misPatientProperties(const misPatientProperties& other);
	~misPatientProperties();

	misPatientProperties& operator=(const misPatientProperties& other);

	int GetAge() const;
	void SetAge(int age);

	std::string GetBirthDate() const;
	void SetBirthDate(const std::string& birthDate);

	// Read image id from DICOM
	misUID      PatientUID;
	long int    NationalCode;
	std::string FirstName;
	std::string FamilyName;
	GenderEnum  Gender;
	int         Weight;
	misPatientPosition Position;
	bool               ReadyForSurgery;
	void  Reset(void);;
	static misPatientPosition StringToPatientPosition(std::string patientPositionString);
	static std::string PatientPositionEnumToString(misPatientPosition position);
	std::map<int, int> GetHistogramMap() const;
	void SetHistogramMap(std::map<int, int> val);
private:
	std::unique_ptr<parcast::DateTime> m_BirthDate;
	std::unique_ptr<parcast::DateTimeOperation> m_DateTimeOps;
	std::unique_ptr<parcast::Clock> m_Clock;
	std::map<int, int> histogramMap;
	double* rangeImage;

public:
	double* RangeImage() const;
	void RangeImage(double* val);
};

typedef  std::vector<misPatientProperties> patientPropertiesTypes;