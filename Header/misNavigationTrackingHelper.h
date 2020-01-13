#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "INavigationTrackingHelper.h"
#include "INavigationViewersNView.h"
#include "ITrackingStateReporter.h"
#include "ITrackingTool.h"
#include "ITrackingToolQuery.h"
#include "ITrackingToolRepository.h"
#include "misGroupViewer.h"
#include "misToolProperties.h"
#include "misTrackingToolMarkerReport.h"
#include "misTrackingToolMarkerReporter.h"
#include "ITracker.h"
#include "ITrackingTooolVisibiltyReport.h"

// The misNavigationTrackingHelper manage navigation tracking tools 
class misNavigationTrackingHelper : public INavigationTrackingHelper
{
public:
	misNavigationTrackingHelper(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager);
	misNavigationTrackingHelper(std::shared_ptr<ITrackingToolQuery> toolQuery,
		std::shared_ptr<ITrackingToolRepository> toolRepository,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		std::shared_ptr<ITracker> tracker, std::shared_ptr<ITrackingTooolVisibiltyReport> visibilityReporter);
	virtual bool IsNavigationToolVisible() override;
	virtual bool IsNavigationToolTipVisibleInrefrenceSpace() const override;
	virtual misTrackingToolMarkerReport GenerateToolVisibiltyReport()override;
	virtual misTrackingStateReport GenerateTrackingReport() override;

	virtual void UpdateNavigationToolTransform(misUID referenceUID) override;
	virtual void RequestNavigationToolCalibration(void) override;
	virtual INavigationTrackingHelper::PointType GetTipPosition() const override;
	virtual itk::Vector<double, 3>  GetNavigationToolDirection(misUID referenceUID) override;
	parcast::VectorD3 GetNavigationToolFaceNormalInImageCoordinate(misUID referenceUID) override;
	virtual void UpdateCalibrationByExtension(double extension) override;
	virtual std::shared_ptr<const ITransform> GetNavToolTransformToRefImage(misUID refrenceUid) override;
	std::string GetNavigationToolDynamicFeatureCoordinateSystem() const;
	size_t GetNumberOfLoadedTools() const override;

private:
	itk::Point<double, 3> UpdateRealTipPosition(std::shared_ptr<const ITransform> transform);
	virtual void UpdateToolData(std::shared_ptr<const ITransform> transform) override;
	virtual std::shared_ptr<const ITransform> GetNavToolRealtipTransformToRefImage(misUID refrenceUid);

	std::shared_ptr<const ITransform> m_NavigationCalibrationTransform;// keep navigation tool transform
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<ITrackingToolQuery> GetToolLocator() const;
	std::shared_ptr<ITrackingTooolVisibiltyReport> GetVisibiltyReporter();

	std::shared_ptr<ITrackingToolQuery> m_ToolLocator;
	std::shared_ptr<ITrackingToolRepository> m_ToolRepository;
	std::shared_ptr<ITracker> m_Tracker;
	itk::Point<double, 3> m_TipPosition;
	bool m_IsNavigationCalibrationTransformSet;
	std::shared_ptr<ITrackingTooolVisibiltyReport> m_VisibiltyReporter;
};
