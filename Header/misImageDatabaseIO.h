#pragma once

#include "misDatabaseIOAbstract.h"
#include "misDatasetIO.h"
#include "misEnumUtilities.h"
#include "misStrctDataSets.h"

#ifndef MISIMAGEDATABASEIO
#define MISIMAGEDATABASEIO

using namespace System;
using namespace System::Data;

typedef std::list<misUID> UIDListTypeddef;

class misImageDatabaseIO : public misDatabaseIOAbstract
{
public:
	misImageDatabaseIO(void);
	bool SetImageListToDB(misSaveSolutionMode savingMode);
	std::shared_ptr<IImage> GetImageDataFromDB(misUID imageUID);
	bool SaveImageContainedPolyDataListToDB(misSaveSolutionMode savingMode);
	void GetImageContainedPolyDataListFromDB();
	void SetSoloutionProperty(std::shared_ptr<misSolutionProperty> val) { m_SoloutionProperty = val; }
	std::vector<std::shared_ptr<IImage>> GetImageListFromDB();


private:
	bool SetImageToDB(std::shared_ptr<IImage> image, misSaveSolutionMode savingMode);
	bool SaveImageDataToDB(std::shared_ptr<IImage> image);
	// Generate auto index file name withou directory - only file name 
	std::string GenerateImageBinaryFileName();
	bool CheckForDeletedImages(UIDListTypeddef imageUIDList, MisObjectType imageType);
	UIDListTypeddef GetExistingImageUIDListFromDB(MisObjectType imageType);
	UIDListTypeddef GetImageUIDList(ImageListTypedef imageList);
	UIDListTypeddef CompareDBImageUIDListWithDatasetManagerImageUIDList( UIDListTypeddef existingImageUIDListOnDB, UIDListTypeddef imageUIDList );
	bool RemoveDeletedImagesFromDB( UIDListTypeddef deletedImageUIDList );

	bool SetImagePropertyToDB(std::shared_ptr<IImage> image);
	bool SetViewingPropertyToDB(std::shared_ptr<IImage> image);
	bool SetStudyPropertyToDB(std::shared_ptr<IImage> image);
	bool SetImagingPropertyToDB(std::shared_ptr<IImage> image);
	bool SetSeriesPropertyToDB(std::shared_ptr<IImage> image);
	bool SetHardwarePropertyToDB(std::shared_ptr<IImage> image);

	misImageProperties        GetImagePropertyFromDB(misUID imageUID);
	misImageViewingProperties GetViewingPropertyFromDB(misUID imageUID);
	misStudyProperties        GetStudyPropertyFromDB(misUID imageUID);
	misImageingProperties     GetImagingPropertyFromDB(misUID imageUID);
	misSerieProperties        GetSeriesPropertyFromDB(misUID imageUID);
	misHardwareProperties     GetHardwarePropertyFromDB(misUID imageUID);


	void DeleteImageContainedPolyDataList();
	UIDListTypeddef GetExistingImageContainedPolydataUIDList();
	PolyDatasPropertyByImageTypdef GetImageContainedPolyDataPropertyFromDB( misUID imageContainedPolyDataUID );
	std::shared_ptr<misSolutionProperty> GetSoloutionProperty() const { return m_SoloutionProperty; }

private:


	bool SaveImageContainedPolyDataToDB( misUID imageContainedPolydataUID, misUID imageUID, misUID parentImageUID );
	bool SetImageContainedPolyDataPropertyListToDB( PolyDatasPropertyByImageTypdef imageContainedPolyDataPropertyList, misUID imageContainedPolydataUID);
	int SetImageContainedPolyDataPropertyToDB(ImagePolyDataContenStrct* imageContainedPolyDataProperty, misUID imageContainedPolyDataUID);

	std::shared_ptr<misSolutionProperty>  m_SoloutionProperty;
	

};

#endif