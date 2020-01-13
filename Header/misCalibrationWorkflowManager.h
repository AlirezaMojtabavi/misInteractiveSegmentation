#pragma once

#include "ICalibrationDataAnalyzer.h"
#include "ICalibrationStrategy.h"
#include "ICalibrationWorkflowManager.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ITimedValidator.h"
#include "ICalibrationProfileFinder.h"

// The misCalibrationWorkflowManager class is a concrete implementation of the ICalibrationWorkflowManager abstract class that
// manages the calibration workflow.
// The workflow manager starts in the ST_INITIAL state. Then, based on the type of the subject tracking tool (fixed or detachable)
// and the user type ("Admin" or "User" defined within properties) determines the next steps as below:
// Admin + fixed/detachable tool OR User + detachable tool (complete calibration profile): 
//		ST_TIP_CALIBRATION_IN_PROGRESS -> ST_TIP_CALIBRATION_SUCCESSFUL -> ST_ORIENTATION_CALIBRATION_STANDBY ->
//		ST_ORIENTATION_CALIBRATION_IN_PROGRESS -> ST_ORIENTATION_CALIBRATION_DONE
//			or (if tip calibration fails)
//		ST_TIP_CALIBRATION_IN_PROGRESS -> ST_TIP_CALIBRATION_FAILED
// User + fixed tool (partial calibration profile): 
//		ST_TIP_VALIDATION_IN_PROGRESS -> (ST_TIP_VALIDATION_SUCCESSFUL or ST_TIP_VALIDATION_FAILED)
// When in any of the idle states, if the automatic calibration is not enabled, UpdateStatus() will return immediately, and 
// state transition to the next IN_PROGRESS state must be carried out through explicit calls to Start(). 
// For smooth calibration, UpdateStatus() must be called in short, regular time intervals. When in any of the IN_PROGRESS states, 
// each call to UpdateStatus() records current tool transform data (subject tool static feature relative to calibration feature on
// the calibration tool), performs fixation analysis (orientation/tip position) on them using respective analyzers, 
// and if a long enough series of recorded data is found to be almost fixed, the data is passed on to the respective calibration
// strategies at each step (tip or orientation). The resulting calibration transform is then applied to the subject tool if it is
// within the defined limits.
// See also ICalibrationStrategy, ICalibrationDataAnalyser.
class misCalibrationWorkflowManager : public ICalibrationWorkflowManager
{
public:
	// The Injector class is used for to create instances of aggregated classes and can be inherited in unit tests to provide 
	// mock objects instead.
	class Injector
	{
	public:
		virtual std::shared_ptr<ICalibrationStrategy> CreateTipCalibrationByMeanStrategy() const;
		virtual std::shared_ptr<ICalibrationStrategy> CreateTipCalibrationBySVDStrategy() const;
		virtual std::shared_ptr<ICalibrationStrategy> CreateOrientationCalibrationByMeanStrategy() const;
		virtual std::shared_ptr<ICalibrationDataAnalyzer> CreateTransformRotationFixationAnalyser(double maxAngularDeviation) const;
		virtual std::shared_ptr<ICalibrationDataAnalyzer> CreateTransformValidPivotAnalyser() const;
		virtual std::shared_ptr<ICalibrationDataAnalyzer> CreateTransformTranslationFixationAnalyser(double maxDeviation) const;
		virtual std::shared_ptr< ITimedValidator< std::shared_ptr<const ITransform> > > CreateTimedTransform(
			std::shared_ptr<const ITransform> transform, bool isTimed, double lifeTime) const;
	};

	// Creates and initializes the workflow manager. The correlation manager passed in will be used throughout the calibration
	// process to retrieve current tool calibration, static tool calibration, and tool position with respect to the calibration
	// feature on the calibrator.
	misCalibrationWorkflowManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, 
		std::shared_ptr<parcast::ICalibrationProfileFinder> calibrationProfileFinder, std::shared_ptr<Injector> injector);

	virtual void Start();
	virtual void Reset();
	virtual void ResetCurrentStep();

	virtual void UpdateStatus();
	virtual misCalibrationWorkflowStatus GetCurrentStatus() const;
	virtual double GetCurrentStateProgress() const;

	virtual void SetSubjectTrackingTool( std::shared_ptr<ITrackingTool> trackingTool );
	virtual std::shared_ptr<const ITrackingTool> GetSubjectTrackingTool() const;

	virtual void SetCalibrationTrackingTool(std::shared_ptr<const ITrackingTool> trackingTool );
	virtual std::shared_ptr<const ITrackingTool> GetCalibrationTrackingTool() const;

	virtual void SetAutomaticCalibration( bool isEnabled );
	virtual bool GetAutomaticCalibration() const;

	virtual void SetProperties( const misCalibrationWorkflowManagerProperties& properties );
	virtual const misCalibrationWorkflowManagerProperties& GetProperties() const;

private:
	typedef itk::Vector<double, 3> VectorType;
	typedef itk::Versor<double> VersorType;

	// Create the orientation and tip calibration strategies and their respective calibration data analyzers based on 
	// current properties. See SetProperties()
	void CreatePipelineElements();

	// Performs one iteration of the tip calibration/validation process. Each iteration begins by appending the latest relative 
	// transform from the calibrating feature on the calibrator to the subject tool static axis feature and pushing it up the 
	// corresponding (tip fixation) calibration data analyzer. Next it checks the analyzer to find out if the collected data 
	// can be used for tip calibration, and if so, it passes the data to tip calibration strategy and retrieves a calibration
	// offset transform. The computed transform now consists of only a translation that translates a point in the calibration
	// feature coordinate system into that of the subject tool static axis feature. The actual calibration transform that will 
	// be set on the subject tool is the current subject tool static axis calibration concatenated before the computed calibration
	// transform. If the computed calibration transform meets thresholds of the current calibration profile, the actual calibration
	// transform is set back on the tool. Finally it transitions the status to success if the offset is below the maximum 
	// deviation and to failure otherwise.
	// If the latest tool transform (received from correlation manager) is not valid (tool not in tracking range?), it returns
	// without further processing.
	void PerformTipCalibrationIteration(
		double maxDeviation, misCalibrationWorkflowStatus successStatus, misCalibrationWorkflowStatus failureStatus);

	std::shared_ptr<const ITransform> GetNewCalibrationDataItem() const;

	// Performs one iteration of the orientation calibration process which is similar to that of PerformTipCalibrationIteration
	// except that orientation fixation analyzer and orientation calibration strategy are used and no threshold checks are 
	// applied and once the calibration transform is computed, first the current static axis orientation calibration and next the 
	// previously set tip calibration transforms are concatenated to it and the combined transform is set back on the tool.
	// It finally transitions the status to ST_ORIENTATION_CALIBRATION_DONE.
	void PerformOrientationCalibrationIteration();
	
	// Applies the current value of m_TemporaryCalibration on the correlation manager so the graphical viewer might be able 
	// to view the tool tip using current calibration. It is not set on tool properties. It is set as a timed transform so
	// after leaving the calibration workflow manager, unless the user accepts the calibration, should the user cancel 
	// the calibration, the temporary calibration will not remain valid and the tool dynamic axis will not be usable.
	void ApplyTemporaryCalibration();

	std::shared_ptr<Injector> m_Injector;	// See Injector
	std::shared_ptr<ITrackingTool> m_SubjectTool;	// See SetSubjectTrackingTool()
	std::shared_ptr<const ITrackingTool> m_CalibrationTool;	// See SetCalibrationTrackingTool()
	bool m_AutomaticCalibration;	// See SetAutomaticCalibration()
	misCalibrationWorkflowStatus m_CurrentStatus;	// See GetCurrentStatus()
	
	// The profile is determined each time new properties or a new subject tracking tool are set based on the user type and the
	// tracking tool type (detachable or fixed). See misCalibrationWorkflowManager.
	misCalibrationWorkflowManagerProperties m_Properties;	// See SetProperties()

	// Used for performing tool tip calibration based on the gathered data
	std::shared_ptr<ICalibrationStrategy> m_TipCalibrationStrategy;

	// Used for performing tool orientation calibration based on the gathered 
	std::shared_ptr<ICalibrationStrategy> m_OrientationCalibrationStrategy;

	// Used for analyzing the data at every iteration of tip calibration to determine if the tool tip position can be 
	// considered fixed
	std::shared_ptr<ICalibrationDataAnalyzer> m_TransformRotationFixationAnalyser;

	// Used for analyzing the data at every iteration of orientation calibration to determine if the tool orientation 
	// can be considered fixed
	std::shared_ptr<ICalibrationDataAnalyzer> m_TransformTranslationFixationAnalyser;

	// Static tool calibration set by factory;
	std::shared_ptr<const ITransform> m_StaticCalibration;

	// Current tool orientation calibration before beginning the process, used for reverting.
	std::shared_ptr<ITransform> m_AfterTipCalibration;

	// Holds the current calibration transform (at each stage of the calibration workflow).
	std::shared_ptr<const ITransform> m_TemporaryCalibration;

	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;	// See ctor()
	std::shared_ptr<parcast::ICalibrationProfileFinder> m_CalibrationProfileFinder;
};