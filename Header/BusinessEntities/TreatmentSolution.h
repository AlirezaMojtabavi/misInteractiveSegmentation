#pragma once

#include "DateTime.h"
#include "IClock.h"
#include "IPackageRepo.h"
#include "ITreatmentSolution.h"
#include "ITreatmentSolutionRepo.h"
#include "Sex.h"

namespace  parcast
{

	class TreatmentSolution : public ITreatmentSolution
	{
	public:
		TreatmentSolution(ITreatmentSolutionRepo::IdType id, const std::string& firstName, const std::string& lastName, Sex sex, 
			const DateTime& birthDate, DateTime& createdTime, std::shared_ptr<IClock> clock, 
			std::shared_ptr<ITreatmentSolutionRepo> solutionRepo, std::shared_ptr<IPackageRepo> packageRepo);

		virtual DateTime GetModifiedTime() const override;
		virtual DateTime GetCreatedTime() const override;
		virtual std::string GetFirstName() const override;
		virtual std::string GetLastName() const override;
		virtual DateTime GetBirthDate() const override;
		virtual Sex GetSex() const override;
		virtual std::vector<std::shared_ptr<IPackage>> GetPackages() const override;
		virtual std::shared_ptr<IPackage> AddNewPackage() override;
		virtual void DeleteSolution() override;

	private:
		ITreatmentSolutionRepo::IdType m_Id;
		std::string m_FirstName;
		std::string m_LastName;
		Sex m_Sex;
		DateTime m_BirthDate;
		DateTime m_CreatedTime;
		DateTime m_ModifiedTime;
		std::shared_ptr<IClock> m_Clock;
		std::shared_ptr<ITreatmentSolutionRepo> m_SolutionRepo;
		std::shared_ptr<IPackageRepo> m_PackageRepo;
	};

}
