#pragma once
#include "misGuiStructures.h"
#include "SurfaceRegistrationDataStrct.h"
#include <string>

class misSurfaceRegistrationErrorReport
{
public:


	misSurfaceRegistrationErrorReport(const SurfaceRegistrationDataStrct& surfaceRegData);

		std::string GetRegisrtationErrorReport();
private:

	std::string GetSurfaceRegistraionReport();
	const SurfaceRegistrationDataStrct& m_SurfaceRegistrationData;
	std::string registrationErrorResult;
};

