#pragma once
#include "misTrackingToolMarkerReport.h"
#include "ITrackingToolQuery.h"
#include "misTrackingStateReporter.h"
#include "misTrackingToolMarkerReporter.h"
#include "ITrackingTooolVisibiltyReport.h"

class misTrackingTooolVisibiltyReport : public ITrackingTooolVisibiltyReport
{
public:
	misTrackingTooolVisibiltyReport(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManger, 
		std::shared_ptr<ITrackingToolQuery> toolQuery, std::shared_ptr<ITrackingToolRepository> toolRepository,
		std::string tracker);
	~misTrackingTooolVisibiltyReport();
		misTrackingStateReport GetToolStateReport() override;
	
		misTrackingToolMarkerReport GetAppropriateToolMarkerVisibilityReport();
	virtual bool RefrenceAndNavigationToolAreVisible() override;
	bool IsToolWithApplicationVisible(misToolProperties::ApplicationFlag flag)  override;

	
private:

	std::shared_ptr<misTrackingToolMarkerReporter> GetToolMarkerReporter(std::shared_ptr<const ITrackingTool> tool)  ;
	std::shared_ptr<misTrackingStateReporter> GetToolStateReporter() ;
	misTrackingToolMarkerReport GenerateToolMarkerReport(misToolProperties::ApplicationFlag appFlag) ;

	bool HasReport(misToolProperties::ApplicationFlag appFlag);

	std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<ITrackingToolRepository> m_ToolRepository;
	std::string m_Tracker;
	std::map<std::shared_ptr<const ITrackingTool>, std::shared_ptr<misTrackingToolMarkerReporter>> m_Reporters;
	std::shared_ptr<misTrackingStateReporter> m_Reporter;

};

