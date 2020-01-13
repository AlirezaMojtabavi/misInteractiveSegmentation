#pragma once
#include "IDatasetManager.h"
#include "INavigationViewersNView.h"
#include "IBiopsyScrewWidgetUpdater.h"

class BiopsyScrewWidgetUpdater : public IBiopsyScrewWidgetUpdater
{
public:
	BiopsyScrewWidgetUpdater(IDatasetManager& datasetManager, std::shared_ptr<ISimpleDataPackage> package);


	void Update(const misScrewWidgetData& screwWidgetVal,
	            misLandmarkInfoStruct& targetLandmarkRelation,
	            misLandmarkInfoStruct& entryLandmarkRelation) final;

private:
	IDatasetManager& m_DatasetManager;
	std::shared_ptr<ISimpleDataPackage> m_Package;
};
