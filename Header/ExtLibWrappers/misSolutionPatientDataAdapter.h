#pragma once

#include "IClock.h"
#include "IDatasetManager.h"
#include "IDateTimeOperation.h"
#include "IPatientDataAccess.h"
#include "ISolutionPatientDataAdapter.h"
#include "ISolutionDataAccess.h"
#include "ICorrelationDataAccess.h"

class misSolutionPatientDataAdapter : public parcast::ISolutionPatientDataAdapter
{
public:
	misSolutionPatientDataAdapter(
		IDatasetManager * datasetManager, 
		std::shared_ptr<parcast::ISolutionDataAccess> solutionDA,
		std::shared_ptr<parcast::IPatientDataAccess> patientDA, 
		std::shared_ptr<parcast::ICorrelationDataAccess> correlationDataAccess,
		std::shared_ptr<parcast::IDateTimeOperation> dateTimeOps, 
		std::shared_ptr<parcast::IClock> clock);
	~misSolutionPatientDataAdapter();

	virtual std::vector<misSolutionProperty> GetAllSolutions() override;
	virtual void SaveSolutionInformation() override;
	virtual void SaveSolutionInformationWithoutRegistration() override;
	virtual void ReadSolutionInformation(const misUID& solutionUid) override;
	virtual void DeleteSolution(const misUID& solutionUid) override;
	virtual void DeleteAllSolutions() override; 

private:
	void SaveSolution(bool includeRegistrationData);

	parcast::SolutionData SolutionPropertyToSolutionData(std::shared_ptr<misSolutionProperty> prop);
	parcast::SolutionData SolutionPropertyToSolutionDataWithoutRegistration(std::shared_ptr<misSolutionProperty> prop);
	parcast::PatientData PatientPropertyToPatientData(const misPatientProperties& patientProperty);
	void SolutionDataToSolutionProperty(misSolutionProperty& solutionProp,
		const parcast::SolutionData & solution, int currentYear);
	misPatientProperties PatientDataToPatientProperty(const parcast::PatientData& patientData, int currentYear);

	std::shared_ptr<parcast::ISolutionDataAccess> m_SolutionDataAccess;
	std::shared_ptr<parcast::IPatientDataAccess> m_PatientDataAccess;
	std::shared_ptr<parcast::ICorrelationDataAccess> m_CorrelationDataAccess;
	IDatasetManager* m_DatasetManager;
	std::shared_ptr<parcast::IClock> m_Clock;
	std::shared_ptr<parcast::IDateTimeOperation> m_DateTimeOps;
};

