#pragma once
// The misVolumeRenderingStrategy class selected volume rendering type and color map whent there is no default volume 
// rendering  for scene based on image type(MRI, Ct, ) 3d model types(number of plans , segmented objcet,...)
class IVolumeRenderingStrategy
{
public:
 
	virtual~IVolumeRenderingStrategy()
	{}

	virtual bool AllImageAreMrAndSegmentedObjectExist() = 0;
	virtual std::shared_ptr<misVolumeData> getVolumeData() const = 0;
	virtual std::shared_ptr<TransFuncIntensity> getTransferFunction(std::shared_ptr<IImage> image) = 0;
	virtual std::shared_ptr<IImage> GetSelctedImage() = 0;
	virtual void SetVolumeViewingType(misVolumeViewingTypes volumeViewingType) = 0;
	virtual int GetNumberOfSegmentedImage() const = 0;
	virtual void SetNumberOfSegmentedImage(int val) = 0;
};