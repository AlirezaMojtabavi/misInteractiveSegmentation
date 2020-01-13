#pragma once

class  ErrorEstimationGetErrorCallback: public itk::Command
{
public:
  typedef ErrorEstimationGetErrorCallback    Self;
  typedef itk::SmartPointer<Self>            Pointer;
  typedef itk::Command                       Superclass;

  itkNewMacro(Self);

  typedef igstk::LandmarkRegistrationErrorEvent 
                         LandmarkRegistrationErrorEventType;

  void Execute( const itk::Object *caller, const itk::EventObject & event )
    {
    }
  void Execute( itk::Object *caller, const itk::EventObject & event )
    {
    std::cout<< " LandmarkRegistrationErrorEvent is thrown" << std::endl;
    const LandmarkRegistrationErrorEventType * errorEvent =
      dynamic_cast < const LandmarkRegistrationErrorEventType* > ( &event );
    m_Error = errorEvent->Get();
    m_EventReceived = true;
    } 
  bool GetEventReceived()
    {
    return m_EventReceived;
    }
  double GetError()
    {
    return m_Error;
    }
protected:
  ErrorEstimationGetErrorCallback()
    {
    m_EventReceived = true;
    }
private:
  bool   m_EventReceived;
  double m_Error;
};

class Landmark3DRegistrationGetRMSErrorCallback: public itk::Command
{
public:
  typedef Landmark3DRegistrationGetRMSErrorCallback  Self;
  typedef itk::SmartPointer<Self>                    Pointer;
  typedef itk::Command                               Superclass;
  itkNewMacro(Self);

  typedef igstk::DoubleTypeEvent DoubleTypeEventType;

  void Execute( const itk::Object *caller, const itk::EventObject & event )
    {
    }
  void Execute( itk::Object *caller, const itk::EventObject & event )
    {
    std::cout<< " DoubleTypeEvent is thrown" << std::endl;
    const DoubleTypeEventType * errorEvent =
                  dynamic_cast < const DoubleTypeEventType* > ( &event );
    m_RMSError = errorEvent->Get();
    m_EventReceived = true;
    } 
  
  bool GetEventReceived()
    {
    return m_EventReceived;
    }
  
  igstk::Transform::ErrorType GetRMSError()
    {
    return m_RMSError;
    }  

protected:
  Landmark3DRegistrationGetRMSErrorCallback()   
    {
    m_EventReceived = true;
    }

private:
  bool m_EventReceived;
  igstk::Transform::ErrorType m_RMSError;
};




class misRegErrorPrediction
 {

	 typedef igstk::Landmark3DRegistrationErrorEstimator   ErrorEstimatorType;
 public:

	 typedef ErrorEstimatorType::TargetPointType   TargetPointType;
	 typedef ErrorEstimatorType::ErrorType         ErrorType;
	  public:

		  ErrorEstimatorType::Pointer errorEstimator;
		  ErrorType                   landmarkRegistrationError;
  ErrorEstimationGetErrorCallback::Pointer lrtcb;
  Landmark3DRegistrationGetRMSErrorCallback::Pointer  lRmscb;
  ErrorType       targetRegistrationError;

	 misRegErrorPrediction(){
	 errorEstimator = ErrorEstimatorType::New();
	 lRmscb=Landmark3DRegistrationGetRMSErrorCallback::New();
	 lrtcb=ErrorEstimationGetErrorCallback::New();
	 }

 //igstk::Landmark3DRegistrationErrorEstimator::ErrorType
 //    misRegErrorPrediction::SetRegistrationError(
	//igstk::Landmark3DRegistration::LandmarkPointContainerType imagePointContainer,igstk::Landmark3DRegistration* landmarkRegister,misRegErrorPrediction::TargetPointType targetPoint);
 //
  

 };