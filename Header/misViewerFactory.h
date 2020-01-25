#pragma once

 #include "misSurgeryDirectionViewerType.h"
#include "IVolume3DRenderer.h"
#include "IViewerFactory.h"
#include "IMultiViewer.h"
#include "LandmarkDataAndType.h"
#include "ILandmarkViewer.h"
#include "misVolumeRendererContainer.h"


class IRepresentationFactory;

class misViewerFactory : public IViewerFactory {

public:
  std::shared_ptr<IVolumeSlicer>
  CreateImageViewer(std::shared_ptr<Iwindows> pWindow,
	  int index,
                    misSurgeryDirectionViewerType currentViewerProp,
                    double VisibilityMarginInAnatomicalPlanesDirection, 
	  bool displayCross,
	  vtkSmartPointer<misInteractorSTyleImageExtend>,
	  misVolumeRendererContainer::Pointer dummy,
	  std::shared_ptr<ICursorService> cursorService, 
	  std::shared_ptr<misCameraInteraction> cameraInteraction) override;
  std::shared_ptr<IVolume3DRenderer>
  CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow, int index,
                     misSurgeryDirectionViewerType currentViewerProp, bool displayCross) override;

  virtual std::shared_ptr<IRepresentationFactory>
  GetRepresentationFactory() const override;


  std::shared_ptr<parcast::ILandmarkViewer> CreateImageLandmarkViewer(std::shared_ptr<IVolumeSlicer>, misViewerTypeDirection viewrType,
	  std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
	  std::shared_ptr<LandmarkDataAndType> landmark, double differenceForViewingSeed,  
	  misVolumeRendererContainer::Pointer dummy, std::shared_ptr<ICursorService> cursorService, 
	  std::shared_ptr<misCameraInteraction> cameraInteraction) override;
};
