#ifndef misTrackingProdecure_H
#define misTrackingProdecure_H

#include "misSequenceManager.h"
#include "misToolAccuracySubSequence.h"
#include "misPolarisTrackingSubsequence.h"
#include "ITrackerConfigure.h"

class misTrackingProdecure : public misSequenceManager {
public:
  misTrackingProdecure(
      misStrctTabModel dataTab,
      std::shared_ptr<ITrackerConfigure> trackingConfig,
      std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
          correlationManager, std::shared_ptr<misSoftwareInformation> softwareInformation);
  virtual void AddCommand(itk::Command *pCommand) override;
  std::shared_ptr<misSubSequence> GetTrackingManager(void);
  misGUIEventConvertor *GetGuiConvertorList();
  std::shared_ptr<misToolAccuracySubSequence> GetToolAc(void);

protected:
  std::shared_ptr<misSubSequence> m_TrackingMangerSubSequence;
  std::shared_ptr<misToolAccuracySubSequence> m_ToolAcuracy;
  std::shared_ptr<ITrackerConfigure> m_TrackerConfig;
};

#endif