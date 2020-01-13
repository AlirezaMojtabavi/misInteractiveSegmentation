#pragma once

#include "misProjectSettingMacro.h"
class misImageIndexData:public Serializable
{
public:
	std::string PatientName;
	std::string StudyDescription;
	std::string SerieDescription;
	int patientindex;
	int studyindex;
	int serieindex;
	int imageindex;

	misImageIndexData(void);

	void Reset(void);
	virtual void serialize(XmlSerializer& s) const;

	virtual void deserialize(XmlDeserializer& s);
};
