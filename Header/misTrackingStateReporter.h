#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "ITrackingStateReporter.h"
#include "ITrackingTool.h"
#include "misToolImageBlender.h"
#include "misTrackingToolQuery.h"
#include "misTrackingToolStateReport.h"

// The misTrackingStateReporter class is a concrete implementation of ITrackingStateReporter that uses a 
// ICoordinateSystemCorrelationManager object and a ITrackingToolRepository to generate tracking reports.
class misTrackingStateReporter : public ITrackingStateReporter
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<ITrackingToolQuery> CreateTrackingToolQuery(std::shared_ptr<ITrackingToolRepository> toolRepo,
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager, std::string trackerUid, 
			const std::vector<IComputedCorrelation::Status> &correlationPriorityList = std::vector<IComputedCorrelation::Status>());
	};
	
	misTrackingStateReporter(std::shared_ptr<ITrackingToolRepository> toolRepo, 
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager, std::string trackerUid,
		std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());

	virtual misTrackingStateReport GenerateReport() override;

	virtual bool IsToolWithApplicationVisible( misToolProperties::ApplicationFlag flag ) const override;

private:
	typedef itk::Point<double, 3> PointType;
	typedef itk::Vector<double, 3> VectorType;

	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<ITrackingToolQuery> m_ToolQuery;
	std::shared_ptr<ITrackingToolRepository> m_ToolRepository;
	std::shared_ptr<Injector> m_Injector;
	std::map<std::string, vtkSmartPointer<vtkTransform>> m_LastToolTransforms;
	std::string m_TrackerUID;
};