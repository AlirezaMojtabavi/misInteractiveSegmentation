#pragma once
#include "IVolumeMaker.h"
#include "IDatasetManager.h"

namespace parcast
{

	class VolumeMaker : public IVolumeMaker
	{
	public:
		VolumeMaker(IDatasetManager* datasetManager);

		void MakeVolumeFromImage(std::weak_ptr<IImage> image, std::weak_ptr<ISimpleDataPackage> package, misApplicationType appType) override;

	private:
		IDatasetManager* m_DatasetManager;
	};

}
