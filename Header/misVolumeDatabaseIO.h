#pragma once

#include "misDatabaseIOAbstract.h"
#include "misEnumUtilities.h"
#include "misVolumeData.h"

#ifndef MISVOLUMEDATABASEIO
#define MISVOLUMEDATABASEIO

using namespace System;
using namespace System::Data;

class misVolumeDatabaseIO : public misDatabaseIOAbstract
{

public :

	misVolumeDatabaseIO(void);

	bool SetVolumeDataListToDB();
	void GetVolumeDataListFromDB();
	misVolumeComponentPropTypdef GetVolumeComponentPropertyListFromDB( misUID volumeDataUID );
	std::string GetSolutionUID() const { return m_SolutionUID; }
	void SetSolutionUID(std::string val) { m_SolutionUID = val; }
private:

	bool SetVolumeDataToDB( std::shared_ptr<misVolumeData>  volumeData );
	bool DeleteVolumeDataListFromDB();
	bool DeleteVolumeComponentPropertyFromDB( misUID volumeDataUID );
	bool SetVolumeComponentProperty( misUID volumeDataUID, misVolumeComponentPropTypdef volumeComponentPropertyMap );
	std::string m_SolutionUID;
	
};

#endif