#pragma once

#include "IVolumeDataDependency.h"

class IImage;
class IVolumeData;

class misVolumeDataDependensies : public IVolumeDataDependency
{
public:
	misVolumeDataDependensies();
	void operator =(misVolumeDataDependensies right);

	// these two items update automatically
	std::shared_ptr<IVolumeData> GetVolume() const override;
	void SetVolume(std::shared_ptr<IVolumeData> val) override;
	std::shared_ptr<IImage> GetImage(void) const override;
	void SetImage(std::shared_ptr<IImage> image) override;
	void SetAllObjectVisibility(const misObjectVisibilityMap &val) override;
	void SetAllObjectVisibility(bool visibility) override;
	// Set color map for specified colormap
	void SetObjectVisibilityProperties(const misUID &uid, const mis3DModelObjectOpacityPropertiesStrct &properties) override;
	void ClearObjectVisibilities() override;
	bool GetObjectVisibilityProperties(const misUID &uid, mis3DModelObjectOpacityPropertiesStrct& model) const override;
	void DeleteObjectVisibility(misUID uid) override;
	bool SetObjectVisibility(const misUID &uid, misPresentationDimension whichScene, bool visibility) override;
	bool SetObjectVisibility(const misUID &uid, bool visibility) override;
	bool SetObjectOpacity(const misUID &uid, misPresentationDimension whichScene, double opacity) override;
	bool SetObjectOpacity(const misUID &uid, double opacity) override;
	misObjectVisibilityMap GetAllObjectVisibility() const override;
	int SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap) override;

	// Volume visibility (colored image such as bone colormap) in 2d viewer is checked by GetObjectVisibilityProperties. When 
	// a volume is being checked whether to be rendered, you must check all colormap visibilities for the volume - the 
	// GetVisibilityIn2D checks visibility for all color maps assigned to the volume in one go (however, its value is set and 
	// retrieved independently of GetObjectVisibilityProperties values. This redundancy must be removed in future versions.
	bool GetVisibilityIn2D() const override;
	void SetVisibilityIn2D(bool val) override;

	misUID GetObjectUID() const override;
	void SetObjectUID(misUID val) override;

	// When there is no default volume, a volume is created using skin threshold for which this flag should be set to true. This
	// volume must not be displayed in GUI or saved to database.
	bool GetAutomaticallyCreated() const override;
	void SetAutomaticallyCreated(bool val) override;
	std::shared_ptr<TransFuncIntensity> GetTransferFunction(misPresentationDimension presentationDim)   override;
	void SetTransferFunction(std::shared_ptr<TransFuncIntensity> transfunction) override;
	std::shared_ptr<TransFuncIntensity> GetTransferFunction() const override;
	void SetParentImageUID(const misUID& uid) override;
	misUID GetParentImageUID()  const override;

private:
	misUID m_ParentImageUID;

	misUID m_ObjectUID;
	bool m_VisibilityIn2D;
	misObjectVisibilityMap  allObjectVisibility;
	std::shared_ptr<IImage> parrentImagePointer;
	std::shared_ptr<IVolumeData> volume;
	bool m_AutomaticallyCreated;
	std::shared_ptr<TransFuncIntensity> m_TransferFunction;
};

typedef std::vector<std::shared_ptr< IVolumeDataDependency>> VolumeDataDependencyListTypes;
