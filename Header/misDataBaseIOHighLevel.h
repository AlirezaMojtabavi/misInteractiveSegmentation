#pragma once

#include "ICoordinateSystemCorrelationsDataAdapter.h"
#include "IDataBaseIO.h"
#include "IDatasetManager.h"
#include "IImageDataAdapter.h"
#include "IPackageDataAdapter.h"
#include "IPlanDataAdapter.h"
#include "ISolutionPatientDataAdapter.h"
#include "IVolumeDataAdapter.h"
#include "Stopwatch.h"
#include "ISegmentedImageDataAdapter.h"
#include "IDataBaseConnection.h"
#include "DatabaseTransaction.h"
#include "ITransactionFactory.h"

class misDataBaseIOHighLevel : public IDataBaseIO
{
public:
	typedef std::list<ICoordinateSystemCorrelationManager<std::string>::DirectCorrelation> CorrelationResultType;

	misDataBaseIOHighLevel(std::shared_ptr<parcast::IDataBaseConnection> dbConnection, 
		std::shared_ptr<parcast::ISolutionPatientDataAdapter> dataEntityIo,
		std::shared_ptr<parcast::IImageDataAdapter> imageDataAdapter,
		std::shared_ptr<parcast::IPackageDataAdapter> packageDataAdapter,
		std::shared_ptr<parcast::ICoordinateSystemCorrelationsDataAdapter> correlationDataAdapter,
		std::shared_ptr<parcast::IPlanDataAdapter> planDataAdapter, 
		std::shared_ptr<parcast::IVolumeDataAdapter> volumeAdapter, 
		std::shared_ptr<parcast::ISegmentedImageDataAdapter> imageContained,
		std::shared_ptr<parcast::IDatabaseTransactionQueryBuilder> transactionQueryBuilder);

	virtual std::vector<misSolutionProperty> GetAllSolutionsList() override;
	virtual bool SaveAllSolutionContent(misSaveSolutionMode savingMode, const misUID& solutionUID) override;
	virtual bool ClearDatabaseContent(void) override;
	virtual void DeleteSolution(misUID solutionUID) override;
	virtual void ReadAllSolutionContent(misUID solutionUID) override;

	virtual void SetDataUploadingSubTabChange(const misUID& solutionUID) override;
	virtual void SetDataCheckingSubTabChange(const misUID& solutionUID) override;
	virtual void SetDataCorrelationSubTabChange(const misUID& solutionUID) override;
	virtual void SetAnalysisProcedureSubTabChange(const misUID& solutionUID) override;
	virtual void SetCompositeMakingSubTabChange(const misUID& solutionUID) override;
	virtual void SetPlanningProcedureSubTabChange(const misUID& solutionUID) override;
	virtual void SetLandMarkSelectionSubTabChange(const misUID& solutionUID) override;
	virtual void SetLandMarkRegistrationSubTabChange() override;

private:
	std::shared_ptr<parcast::IDataBaseConnection> m_DbConnection;
	std::shared_ptr<parcast::ISolutionPatientDataAdapter> m_SolutionPatientDataAdapter;
	std::shared_ptr<parcast::IImageDataAdapter> m_ImageDataAdapter;
	std::shared_ptr<parcast::IPackageDataAdapter> m_PackageDataAdapter;
	std::shared_ptr<parcast::ICoordinateSystemCorrelationsDataAdapter> m_CorrelationDataAdapter;
	std::shared_ptr<parcast::IPlanDataAdapter> m_PlanDataAdapter;
	std::shared_ptr<parcast::IVolumeDataAdapter> m_VoumeDataAdapter;
	std::shared_ptr<parcast::ISegmentedImageDataAdapter> m_ImageContainedDataAdapter;
	std::shared_ptr<parcast::ITransactionFactory> m_TransactionFactory;

	std::ofstream m_TimeLogger;
	Stopwatch m_Timer;
};