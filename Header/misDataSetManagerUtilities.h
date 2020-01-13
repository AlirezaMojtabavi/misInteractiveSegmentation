#pragma once

#include "misEnums.h"
#include "misPlanData.h"
#include "misSimpleDataPackage.h"
#include "misStrctDataSets.h"
#include "misStringTools.h"
#include "misVolumeData.h"

class misCompositeDataPackage;
class  misDataSetManagerUtilities
{

public:
	static   bool     FindDuplicatedPackageInDatasetManager (PackagesListTypedef packageList, misUID  packageUID);
	static   bool     FindDuplicatedImageInDataset (ImageListTypedef imageList ,misUID imagePrimeryUID);
	static   bool     FindDuplicatedVolumeDataInDataset(VolumeDataListTypedef*  volumedataList,misUID  volumeDataUID, misUID parrentImageUID);
		static	std::string   MakeBinaryFileName(MisObjectType objectType, int objectNumber);
	static void UpdatePackageNames(PackagesListTypedef packageList);
	misDataSetManagerUtilities(void);
	~misDataSetManagerUtilities(void);

private:
	static PackagesListTypedef UpdateSimplePackageNames( PackagesListTypedef packageList );

	// Update composite package name by using package names that contain images of composite package - if 2 composite package 
	// have same image their name must be different
	static void UpdateCompositePackageNames(const PackagesListTypedef &packageList);

	// If 2 or more package have an equal name make them different by adding index at end
	static void RenameDuplicateNames( const PackagesListTypedef &packageList );

	// Returns simple package names that contain provided image UIDs
	static std::vector<misUID> GetPackageNamesByImageUids( const PackagesListTypedef &simplePackageList, 
		const std::vector<misUID> &ImageUIDs);

	// Return UIDs of package images
	static std::vector<misUID> GetPackageImageUids(std::shared_ptr<misCompositeDataPackage> compositePack);

	static std::string GetPackageName( misImageDataModality Imagemodality, int counter );

};

 
