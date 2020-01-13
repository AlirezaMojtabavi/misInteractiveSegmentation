#pragma once

#include "DateTime.h"

namespace parcast
{
	struct PatientData
	{
		std::string PatientUID;
		std::string	Name;
		std::string	FamilyName;
		std::string Gender;
		std::string Position;
		std::string NationalCode;
		DateTime BirthDate;
		int	Weight = 0;
	};
}
