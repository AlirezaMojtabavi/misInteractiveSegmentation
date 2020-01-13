#pragma once
#include "mis3DModelViewingProperties.h"
#include "misEnums.h"

class IVolumeData;
class IImage;
 
class IVolumeDataDependency
{
public:
	virtual ~IVolumeDataDependency() = default;
	virtual std::shared_ptr<IVolumeData> GetVolume() const = 0;
	virtual  void SetVolume(std::shared_ptr<IVolumeData> val) = 0;
	virtual  std::shared_ptr<IImage> GetImage(void) const = 0;
	virtual  void SetImage(std::shared_ptr<IImage> image) = 0;
	virtual  void SetAllObjectVisibility(const misObjectVisibilityMap &val) = 0;
	virtual  void SetAllObjectVisibility(bool visibility) = 0;
	virtual  void SetObjectVisibilityProperties(const misUID &uid, const mis3DModelObjectOpacityPropertiesStrct &properties) = 0;
	virtual  void ClearObjectVisibilities() = 0;
	virtual  bool GetObjectVisibilityProperties(const misUID &uid, mis3DModelObjectOpacityPropertiesStrct& model) const = 0;
	virtual  void DeleteObjectVisibility(misUID uid) = 0;
	virtual  bool SetObjectVisibility(const misUID &uid, misPresentationDimension whichScene, bool visibility) = 0;
	virtual  bool SetObjectVisibility(const misUID &uid, bool visibility) = 0;
	virtual  bool SetObjectOpacity(const misUID &uid, misPresentationDimension whichScene, double opacity) = 0;
	virtual  bool SetObjectOpacity(const misUID &uid, double opacity) = 0;
	virtual  misObjectVisibilityMap GetAllObjectVisibility() const = 0;
	virtual  int SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap) = 0;
	 // Volume visibility (colored image such as bone colormap) in 2d viewer is checked by GetObjectVisibilityProperties. When 
	 // a volume is being checked whether to be rendered, you must check all colormap visibilities for the volume - the 
	 // GetVisibilityIn2D checks visibility for all color maps assigned to the volume in one go (however, its value is set and 
	 // retrieved independently of GetObjectVisibilityProperties values. This redundancy must be removed in future versions.
	virtual  bool GetVisibilityIn2D() const = 0;
	virtual  void SetVisibilityIn2D(bool val) = 0;
	virtual  misUID GetObjectUID() const = 0;
	virtual  void SetObjectUID(misUID val) = 0;
	  // When there is no default volume, a volume is created using skin threshold for which this flag should be set to true. This
	  // volume must not be displayed in GUI or saved to database.
	virtual  bool GetAutomaticallyCreated() const = 0;
	virtual  void SetAutomaticallyCreated(bool val) = 0;
	virtual  std::shared_ptr<TransFuncIntensity> GetTransferFunction(misPresentationDimension presentationDim)   = 0;
	virtual  void SetTransferFunction(std::shared_ptr<TransFuncIntensity> transfunction) = 0;
	virtual  std::shared_ptr<TransFuncIntensity> GetTransferFunction() const = 0;
	virtual void SetParentImageUID(const misUID& uid) = 0;
	virtual misUID GetParentImageUID()  const = 0;

};
