#pragma once

#include "DateTime.h"

namespace parcast
{
	struct SolutionData
	{
		std::string SolutionUid;
		std::string PatientUid;
		std::string UserId;
		DateTime DateTimeOfCreation;
		std::string SolutionFolderName;
		DateTime DateTimeOfModification;
		bool IsViewable = false;
		std::string LastSelectedTabName;
		std::string LastSelectedSubTabName;
		std::string RegisteredImageUid;
		std::string RegisteredReferenceUid;
	};
}



