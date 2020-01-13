#pragma once

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "misIntegrationTestApplication.h"
#include "igstkPivotCalibrationAlgorithm.h"
#include "ITrackerConfigure.h"

enum TrackerType;

/** Class for observing the invalid request error.*/
class InvalidRequestErrorEventObserver : public itk::Command
{
public:
	typedef InvalidRequestErrorEventObserver            Self;
	typedef itk::SmartPointer<Self>                     Pointer;
	typedef itk::Command                                Superclass;
	itkNewMacro(Self);

	void Execute(const itk::Object *caller, const itk::EventObject & event)
	{
		const itk::Object * constCaller = caller;
		this->Execute(constCaller, event);
	}

	void Execute(itk::Object *caller, const itk::EventObject & event)
	{
		std::cout << "Invalid method request, cannot invoke this method in current ";
		std::cout << "object state." << std::endl;
		this->m_EventOccured = true;
	}

	bool EventOccured()
	{
		return this->m_EventOccured;
	}

	void Reset()
	{
		this->m_EventOccured = false;
	}

protected:
	InvalidRequestErrorEventObserver() : m_EventOccured(false) {}
	virtual ~InvalidRequestErrorEventObserver() {}

private:
	InvalidRequestErrorEventObserver(const Self&);
	void operator=(const Self&);

	bool m_EventOccured;
};


/** Class for observing events that carry a payload. The user can query the
 *  class if an event occured (EventOccured), access the payload (Get()), and
 *  reset (EventOccured==false) the observer (Reset()).*/
template <class EventType>
class PayloadEventObserver : public itk::Command
{
public:
	typedef PayloadEventObserver            Self;
	typedef itk::SmartPointer<Self>         Pointer;
	typedef itk::Command                    Superclass;
	itkNewMacro(Self);

	void Execute(const itk::Object *caller, const itk::EventObject & event)
	{
		const itk::Object * constCaller = caller;
		this->Execute(constCaller, event);
	}

	void Execute(itk::Object *caller, const itk::EventObject & event)
	{
		const EventType *evt = dynamic_cast<const EventType *> (&event);
		if (evt)
		{
			this->m_EventOccured = true;
			this->m_Payload = evt->Get();
		}
	}

	typename EventType::PayloadType Get()
	{
		return this->m_Payload;
	}

	bool EventOccured()
	{
		return this->m_EventOccured;
	}

	void Reset()
	{
		this->m_EventOccured = false;
	}

protected:
	PayloadEventObserver() : m_EventOccured(false) {}
	virtual ~PayloadEventObserver() {}

private:
	PayloadEventObserver(const Self&);
	void operator=(const Self&);

	bool m_EventOccured;
	typename EventType::PayloadType m_Payload;
};


typedef PayloadEventObserver< igstk::CoordinateSystemTransformToEvent >
TransformEventObserver;
typedef PayloadEventObserver< igstk::PointEvent > PivotPointEventObserver;
typedef PayloadEventObserver< igstk::DoubleTypeEvent > RMSEEventObserver;


class CalibrationEventObserver : public itk::Command
{
public:
	typedef CalibrationEventObserver            Self;
	typedef itk::SmartPointer<Self>             Pointer;
	typedef itk::Command                        Superclass;
	itkNewMacro(Self);

	void Execute(const itk::Object *caller, const itk::EventObject & event)
	{
		const itk::Object * constCaller = caller;
		this->Execute(constCaller, event);
	}

	void Execute(itk::Object *caller, const itk::EventObject & event)
	{
		if (dynamic_cast<const igstk::PivotCalibrationAlgorithm::CalibrationSuccessEvent *> (&event))
		{
			std::cout << "Calibration succeeded." << std::endl;
			this->m_Success = true;
		}
		else if (dynamic_cast<const igstk::PivotCalibrationAlgorithm::CalibrationFailureEvent *> (&event))
		{
			std::cout << "Calibration failed." << std::endl;
			this->m_Failure = true;
		}
	}

	bool SuccessEventOccured()
	{
		return this->m_Success;
	}

	bool FailureEventOccured()
	{
		return this->m_Failure;
	}

	void Reset()
	{
		this->m_Success = false;
		this->m_Failure = false;
	}

protected:
	CalibrationEventObserver() : m_Success(false), m_Failure(false) {};
	virtual ~CalibrationEventObserver() {}

private:
	CalibrationEventObserver(const Self&);
	void operator=(const Self&);

	bool m_Success;
	bool m_Failure;
};


class CalibrationProfile :public Serializable
{
public:
	CalibrationProfile();
	std::string calibrationTool;
	std::string referenceSystem;
	unsigned int sampleNumber;

	virtual void serialize(XmlSerializer& s) const;

	virtual void deserialize(XmlDeserializer& s);

};
// The misScremisAscentionCalibration class creates and initialize tracker b
class misPivotCalibration : public misIntegrationTestApplication
{
public:
	misPivotCalibration(int &argc, char ** argv);



	void ReadCalibrationProfile();

private:
	virtual void PulseHandler() override;

	void SaveResults(const int sampleNumberTotal);

	void AvergaeCalibrationOffset(std::shared_ptr<ITrackingTool> selctedTool);

	itk::Point<double, 3> CalculatePivotPoint();

	void CollectTrasforms(std::shared_ptr<ITrackingTool> selctedTool);

	void AddRepresentations(TrackerType trackerType, std::vector<std::shared_ptr<ITrackingTool>> addedTool);

	void InitilizeCalibrationObserver();

	void FindCoordinates();

	std::string FindRferenceCoordinate(std::list<std::shared_ptr<ITrackingTool>> tools);

	std::shared_ptr<ITrackingTool> FindCalibrationTool(std::list<std::shared_ptr<ITrackingTool>> tools);
	std::shared_ptr<ITrackerConfigure> m_TrackingConfigure;
	std::shared_ptr<I3DViewer> m_Viewer;
	std::shared_ptr<misCoordinateSystemCorrelationTreeManager> m_correlationManager;
	std::vector< igstk::Transform > transformations;
	igstk::Transform::VectorType translation;
	igstk::Transform::VersorType rotation;
	igstk::Transform currentTransform, computedTransform1, computedTransform2;
	igstk::Transform composedTransform;
	itk::Point< double, 3 > pivotPoint1, pivotPoint2;
	double calibrationRMSE1, calibrationRMSE2;
	//the class we are testing
	igstk::PivotCalibrationAlgorithm::Pointer pivotCalibrationAlgorithm;
	InvalidRequestErrorEventObserver::Pointer invalidRequestErrorObserver;
	CalibrationEventObserver::Pointer calibrationEventObserver;
	TransformEventObserver::Pointer transformEventObserver;
	PivotPointEventObserver::Pointer pivotPointEventObserver;
	RMSEEventObserver::Pointer rmseEventObserver;
	double average[3];
	itk::Point<double, 3>  m_pivotPoint;

	bool m_SavedResult;
	CalibrationProfile m_Profile;
	std::shared_ptr<ITrackingTool> m_CalibrationTool;
	std::string m_RefrenceCoordinateUID;
};