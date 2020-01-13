#pragma once

#include <map>

#include "ICoordinateSystem.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ITimedValidator.h"
#include "ITrackingTool.h"
#include "igstkTrackerTool.h"
#include "igstkTransformObserver.h"
#include "itkVector.h"
#include "misDejitterizedValue.h"
#include "misToolProperties.h"
#include "misTrackingEvents.h"
#include "IAppySmoothingDecider.h"
#include "ITrackerToolFactory.h"

//igstkLoadedEventMacro(misInterference, misEvent, bool);

class misToolData : public ITrackingTool
{
public:
	typedef itk::Versor<double> VersorType;
	typedef itk::Vector<double> VectorType;
	class Injector
	{
	public:
		virtual std::shared_ptr<ICoordinateSystem> CreateCoordinateSystem(const std::string& uid) const;
		virtual std::shared_ptr< const ITimedValidator<std::shared_ptr<const ITransform>> > CreateTimedTransform(
			std::shared_ptr<const ITransform> newValue, bool isTimed, double lifeTime) const;
		virtual std::shared_ptr<ITransform> CreateTransform(const tgt::Matrix4d& matrix) const;
	};

	enum toolDataGatheringStatus
	{
		ContineusGhadering,
		FirstJitterHappend,
		MovingTool
	};

	misToolData(TrackerType typeOfTracker,
		const misToolProperties& toolProperties,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >,
		std::shared_ptr<parcast::ITrackerToolFactory> trackerToolFactory,
		std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());
	~misToolData();

	// Construction/initialization level methods not inherited from interface:
	void SetTracker(igstk::Tracker* tracker) override;
	void SetDejitterizerHistoryLength(int historyLength) override;
	void SetDejitterizerKernel(const std::vector<double>& kernelCoefficients) override;

	void ApplyToolCalibrationTransform(std::string currentPatientUid) override;
	bool DetachFromTracker() override;
	// Other methods not inherited from interface: 

	// ICoordinateSystem interface:
	virtual std::string GetUID() const override;

	// ITrackingTool interface:
	virtual double GetTipValidationDistanceThreshold() const override;
	virtual double GetTipCalibrationDistanceThreshold() const override;
	virtual double GetOrientationCalibrationAngleThreshold() const override;
	virtual double GetPositionFixationDistanceThreshold() const override;
	virtual double GetOrientationFixationAngleThreshold() const override;
	virtual time_t GetLastCalibrationTimeTag() const override;
	virtual void SetLastCalibrationTimeTag(time_t timeTag) override;
	virtual std::shared_ptr<const ICoordinateSystem> GetAxisStaticFeature() const override;
	virtual std::shared_ptr<const ICoordinateSystem> GetAxisDynamicFeature() const override;
	virtual void SetCalibrationTransform(std::shared_ptr<const ITransform> transform) override;
	virtual const VectorType& GetTipCalibrationViewCameraPosition() const override;
	virtual const VectorType& GetOrientationCalibrationViewCameraPosition() const override;
	virtual const VectorType& GetTipCalibrationViewCameraFocalPoint() const override;
	virtual const VectorType& GetOrientationCalibrationViewCameraFocalPoint() const override;
	virtual std::shared_ptr<const ICoordinateSystem> GetCalibrationFeature() const override;
	virtual const misToolProperties& GetToolProperties(void) const override;
	virtual igstk::Tracker* GetTracker() const override;
	virtual std::string GetTrackerUID() const override;
	virtual igstk::TrackerTool::Pointer GetTrackedTool() const override;
	virtual bool HasApplicationFlag(misToolProperties::ApplicationFlag flag) const override;
	virtual void SetToolStatus(misToolStatus status) override;
	virtual std::string GetPatientUid() const;
	virtual void SetPatientUid(const std::string& patientUid);
	virtual std::string GetToolName()const override;

	void SetSmoothingDecider(std::shared_ptr<IApplySmoothingDecider> val) override;

	virtual void SetUID(const std::string& id) override;

	std::shared_ptr<IApplySmoothingDecider> GetSmoothingDecider() const override;
private:

	// functions related to tracker observer
	void CheckCalibration();
	void ObserveTransformChange(itk::Object *caller, const itk::EventObject & event);
	void UpdateToolTransform(void);

	virtual ToolExtraInformation GetTrackedToolExtraInformation() const;


	VectorType m_TipCalibrationViewCameraPosition;
	VectorType m_OrientationCalibrationViewCameraPosition;
	VectorType m_TipCalibrationViewCameraFocalPoint;
	VectorType m_OrientationCalibrationViewCameraFocalPoint;
	misDejitterizedValue<tgt::Matrix4d> m_DejitterizedToolTransform;
	std::function<double(int index, int totalCount)> m_DefaultDejitterizerWeightFunction =
		m_DejitterizedToolTransform.GetWeightFunction();

	igstk::Tracker*	m_Tracker;
	igstk::TrackerTool::Pointer m_TrackedTool;
	igstk::TransformObserver::Pointer	m_ToolTransformObserver;
	misToolProperties	m_ToolProperty;
	std::shared_ptr<ICoordinateSystem>  m_AxisStaticFeature;
	std::shared_ptr<ICoordinateSystem>  m_AxisDynamicFeature;
	std::shared_ptr<ICoordinateSystem>	m_CalibrationFeature;
	std::shared_ptr<Injector>			m_Injector;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	time_t m_TimeToolWasFirstObserved;
	double m_WaitTimeBeforeCalibrationStarts;	// In milliseconds
	std::shared_ptr<IApplySmoothingDecider> m_SmoothingDecider;
	std::ofstream m_TrackerLogger;
};

typedef std::vector<std::shared_ptr<misToolData>> TrackerToolDataListType;