#pragma once
#include "ICoordinateSystemCorrelationManager.h"
#include "IDatasetManager.h"
#include "ITracker.h"
#include "ITrackerConfigure.h"
#include "ITrackingToolQuery.h"
#include "ITrackingToolRepository.h"
#include "misSmoothingDeciderFactory.h"
#include "misToolData.h"
#include "misToolProperties.h"
#include "misTrackingManagerTypes.h"

class misTrackerConfigure : public ITrackerConfigure {
public:
  class Injector {
  public:
    virtual std::shared_ptr<ITrackingTool> CreateTooldata(
        std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
            correlationTree,
        const misToolProperties &data, const std::string &currentPatientUid,
        TrackerType trackerType);
  };
  misTrackerConfigure(
      std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
          correlationManager,
      std::shared_ptr<ITracker> tracker,
      std::shared_ptr<ITrackingToolQuery> toolQuery,
      std::shared_ptr<ITrackingToolRepository> toolRepo,
      IDatasetManager *datasetMngr, TrackerType trackerType,
      std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());
  void DeleteTool(misStrctSimpleToolProperties ToolPropFromGui) override;
  void AddObserversAddTools(misToolPropertiesListTypdef ListOfTools) override;
  void MakeAndSendAddEvent(std::shared_ptr<ITrackingTool> ms) override;
  std::vector<std::shared_ptr<ITrackingTool>>
  AddToolList(misToolPropertiesListTypdef ToolList) override;
  std::shared_ptr<ITrackingTool> MakeTool(misToolProperties data) override;
  void CheckTrackerConnectivity() override;
  bool ResetTracker();
  void CloseTracker() override;
  virtual bool Connect(misStrctComConnectionOptions connecting) override;
  virtual igstk::Tracker *GetTracker() override;
  virtual unsigned long AddObserver(const itk::EventObject &event,
                                    itk::Command *) override;
  virtual void SetConnectionFailureFlag(bool flag) override;
  virtual bool GetConnectionFailureFlag() override;
  bool GetTrackerDisconnected() const override;
  void SetSmoothingDecider(
      std::shared_ptr<misSmoothingDeciderAbstarctFactory> val) override;

private:
  void ObserveDisconnection();
  void TrackerCallback(itk::Object *caller, const itk::EventObject &event);
  void TrackerDisconnectedEventCallback(itk::Object *caller,
                                        const itk::EventObject &event);

  std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
      m_CSCorrelationManager;
  std::shared_ptr<ITracker> m_Tracker;
  std::shared_ptr<ITrackingToolQuery> m_ToolLocator;
  itk::MemberCommand<misTrackerConfigure>::Pointer m_TrackingMangerObserver;
  std::shared_ptr<ITrackingToolRepository> m_ToolRepo;
  itk::Object::Pointer m_dummyObjectInvoker;
  bool m_TrackerDisconnected;
  std::shared_ptr<Injector> m_Injector;
  IDatasetManager *m_DataSetmanger;
  TrackerType m_TrackerType;
  bool m_ConnectionFailed;
  itk::SimpleMutexLock m_Mutex;
  std::shared_ptr<misSmoothingDeciderAbstarctFactory> m_SmoothingDecider;
  bool  m_UserDenyTrackingConnection = false;;
};
