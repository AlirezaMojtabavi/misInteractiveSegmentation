#pragma once

#include "misDatabaseIOAbstract.h"
#include "misEnumUtilities.h"
#include "misSTRCT.h"
#include "ISimpleDataPackage.h"
#include "misStrctDataSets.h"
#include "misPanoramicDataSqlDbAdaptor.h"

#ifndef MISPACKAGEDATABASEIO
#define MISPACKAGEDATABASEIO

using namespace System;
using namespace System::Data;

class misPackageDatabaseIO : public misDatabaseIOAbstract
{


public :

	misPackageDatabaseIO(void);

	bool SetPackageListToDB(const misUID& solutionUID);
	void GetPackageListFromDB(const misUID& solutionUID);

	bool SetPackageToDB(std::shared_ptr<ISimpleDataPackage> package, const misUID& solutionUID);
	bool SetPackageInformationToDB(std::shared_ptr<ISimpleDataPackage> package, const misUID& solutionUID);
	bool SetImageDependencylistToDB(ImageDependencyListTypes* imageDependencyList);	
	bool SetImageDependencyToDB( const misCompeleteImageDependencies&  imageDependencyStrct) const;
	ImageDependencyListTypes GetImageDependencylistFromDB(misUID packageUID);
	void CreatePlanDataDependencyListFromDB(std::shared_ptr<ISimpleDataPackage> package);
	bool SetLandmarkToDB(std::shared_ptr<ISimpleDataPackage> package);
	misLandmarkListTypdef GetLandmarkFromDB(misUID packageUID);

	bool DeleteExistingPackages(misUID solutionUID);

	bool SetImageContainedPolyDataDependencyListToDB( ImageContainedPolydataDependencyListTypes* imageContainedPolyDataDependencyList );
	bool SetPlanDataDependencyListToDB(std::shared_ptr<PlanDataListDependencyTypedef> planDataDependencyList);
	bool SetImageContainedPolydDataDependencyToDB( std::shared_ptr<misCompeleteImageContainedPolydataDependensiesStrct> imageContainedPolyDataDependencyStructure );
	bool Set3DModelVisibilityDependencyToDB(mis3DModelObjectOpacityPropertiesStrct objectVisibilityProperty, misUID objectUID, misUID PackageUID, misUID objectContainerUID);
	void Delete3DModelVisibilityDependencyFromDB( misUID packageUID );
	void DeleteImageContainedPolyDataDependencyFromDB(misUID packageUID);
	void DeleteImageDependencyFromDB( misUID packageUID );
	void DeletePlanDependencyFromDB( misUID packageUID );
	void DeleteDependencies( misUID packageUID );
	ImageContainedPolydataDependencyListTypes GetImageContainedPolyDataDependencyListFromDB( misUID packageUID );
	misObjectVisibilityMap Get3DModelVisibilityDependencyFromDB( misUID packageUID, misUID imageContainedPolyDataDependencyUID );

	bool SetVolumeDataDependencyListToDB( VolumeDataDependencyListTypes* volumeDataDependencyList );
	bool SetVolumeDataDependencyToDB(std::shared_ptr<misVolumeDataDependensies> volumeDataDependencyStruct );
	void DeleteVolumeDataDependencyFromDB( misUID packageUID );
	VolumeDataDependencyListTypes GetVolumeDataDependencyListFromDB( misUID packageUID );
private:

	misUID m_CurrentPackageUID;
	misPanoramicDataSqlDbAdaptor m_panoramicDataBaseAdaptor;

	bool SetPlanDependencyToDB( std::shared_ptr<misCompeletePlanDataDependensiesStrct> planDataDependencyList );
};

#endif