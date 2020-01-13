#pragma once

class misTrackingStateReport;
class ITransform;

template < typename CST >
class ICoordinateSystemCorrelationManager;

struct misTrackingToolMarkerReport;

typedef std::string misUID;

namespace  parcast
{
	using VectorD3 = Vector<double, 3>;
}

class INavigationTrackingHelper
{
public:
	typedef itk::Point<double,3> PointType;
	typedef itk::Vector<double,3> VectorType;

	virtual bool IsNavigationToolVisible() = 0;
	virtual bool IsNavigationToolTipVisibleInrefrenceSpace() const = 0;
 	virtual misTrackingStateReport GenerateTrackingReport() = 0;
	virtual misTrackingToolMarkerReport GenerateToolVisibiltyReport( ) = 0;
	virtual void UpdateNavigationToolTransform(misUID referenceUID ) = 0;
	virtual void UpdateToolData(std::shared_ptr<const ITransform> transform) = 0;
	virtual void RequestNavigationToolCalibration( void ) = 0;
	virtual PointType GetTipPosition() const = 0;
	virtual VectorType GetNavigationToolDirection(misUID referenceUID) = 0;
	virtual void UpdateCalibrationByExtension(double extension ) = 0;
	virtual std::shared_ptr<const ITransform> GetNavToolTransformToRefImage(misUID refrenceUid) = 0;
	virtual parcast::VectorD3 GetNavigationToolFaceNormalInImageCoordinate(misUID referenceUID) = 0;
	virtual size_t GetNumberOfLoadedTools() const = 0;
	virtual std::string GetNavigationToolDynamicFeatureCoordinateSystem() const = 0;
	virtual ~INavigationTrackingHelper() { }
};