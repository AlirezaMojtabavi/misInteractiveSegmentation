#pragma once

#include "misEnums.h"
#include "serializable.h"
#include "misCTLevelWindowStr.h"
#include "misMRILevelWindowStr.h"  

struct misDataUploadingSetting : public Serializable
{
private:
	int		m_AtleastMinimumImageNumberIsAccptedForNavigation; // Important Note : must not serialize
	double  m_MaximumMaxImageSpacaingIsAccptedForNavigation;   // Important Note : must not serialize
	void SetDefaultPresetContrastValues();

public:
	bool	LoggerEnabled;
	bool    LogDicomData;
	bool	m_UseThredaForFolderAnalysis;
	bool	m_UesThredaForDicomReading;
	bool    m_CopyPatientCDOnHard;
	bool	m_CheckDataRepresentation;
	int		m_MinimumImageNumberIsAccptedForNavigation;

	double  m_MaxMRIRange;
	double  m_MinMRIRange;
	double  m_MaxCTRange;
	double  m_MinCTRange;
	double  m_MaxImageSpacaingIsAccptedForNavigation;

	std::string m_TmpFolderPathForUncompressedData;

	misCTLevelWindowStr CTLevelWindowParam;
	misMRILevelWindowStr MRILevelWindowParam;
	std::map<misImageViewingType, misWindowLevelStr> m_DefaultWindowLevelViewingMap;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	 misDataUploadingSetting(void);
};
