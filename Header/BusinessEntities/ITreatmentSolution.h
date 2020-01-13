#pragma once

class ISimpleDataPackage;

namespace parcast
{
	// The ITreatmentSolution class provides the abstract interface to a complete treatment/surgery solution data 
	// including patient properties, medical images, packages, plans, tracker, tracker tools, landmarks, registrations,
	// relationships between objects, ...
	class ITreatmentSolution
	{
	public:

		virtual ~ITreatmentSolution() { }

		virtual std::vector<std::shared_ptr<ISimpleDataPackage>> GetPackages() const = 0;
	};

}
