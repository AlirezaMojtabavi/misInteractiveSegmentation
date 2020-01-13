#pragma once

 #include "misSurgeryDirectionViewerType.h"
#include "IVolume3DRenderer.h"
#include "IViewerFactory.h"
#include "IMultiViewer.h"
 
class IRepresentationFactory;

class misViewerFactory : public IViewerFactory {

public:
  std::shared_ptr<misVolumeSlicer>
  CreateImageViewer(std::shared_ptr<Iwindows> pWindow, int index,
                    misSurgeryDirectionViewerType currentViewerProp,
                    double VisibilityMarginInAnatomicalPlanesDirection, bool displayCross) override;
  std::shared_ptr<IVolume3DRenderer>
  CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow, int index,
                     misSurgeryDirectionViewerType currentViewerProp, bool displayCross) override;

  virtual std::shared_ptr<IRepresentationFactory>
  GetRepresentationFactory() const override;



};
