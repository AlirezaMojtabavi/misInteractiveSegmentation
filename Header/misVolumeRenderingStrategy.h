#pragma once
#include "misStrctDataSets.h"
#include "misVolumeData.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "..\misNavigationFourView\IVolumeRenderingStrategy.h"

// The misVolumeRenderingStrategy class selected volume rendering type and color map whent there is no default volume 
// rendering  for scene based on image type(MRI, Ct, ) 3d model types(number of plans , segmented objcet,...)
class misVolumeRenderingStrategy : public IVolumeRenderingStrategy
{
public:
	misVolumeRenderingStrategy(ImageDependencyListTypes currentImageDataDependencies, 
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, misVolumeViewingTypes volumeViewing,
		int numberOfSegmentedIMage);

	bool AllImageAreMrAndSegmentedObjectExist();
	std::shared_ptr<misVolumeData> getVolumeData() const;
	std::shared_ptr<TransFuncIntensity> getTransferFunction(std::shared_ptr<IImage> image);
 	std::shared_ptr<IImage> GetSelctedImage();	
	void SetVolumeViewingType(misVolumeViewingTypes volumeViewingType);

	int GetNumberOfSegmentedImage() const;
	void SetNumberOfSegmentedImage(int val);
private:
		
	std::shared_ptr<IImage> FindFirtstCtImage() const;
	int getNumberOfMriImages() const;
	std::shared_ptr<IImage> m_CTImage;
	std::shared_ptr<IImage> m_SelectedImage;

	std::shared_ptr<misVolumeData>	m_DefaultVolumeData;
	ImageDependencyListTypes m_CurrentImageDataDependencies;
	misVolumeViewingTypes m_VolumeViewingType;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	int m_NumberOfSegmentedImage;
	
};

