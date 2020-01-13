#pragma once

#include "ISimpleDataPackage.h"
#include "misResultCode.h"
#include "IVolumeFactory.h"
#include "VolumeFactory.h"


template < typename CST >
class ICoordinateSystemCorrelationManager;

class misCompeleteImageContainedPolydataDependensiesStrct;
class IVolumeDataDependency;
class IImage;

namespace parcast
{
	class IPackagePlanRelRepo;
}

class misSimpleDataPackage : public ISimpleDataPackage, public std::enable_shared_from_this<misSimpleDataPackage>
{
public:
	misSimpleDataPackage(std::shared_ptr<parcast::IPackagePlanRelRepo> packagePlanRelRepo);
	~misSimpleDataPackage();

	void SetObjectUID(const misUID& dataUID) override;
	misUID GetObjectUID() const override;
	void SetName(std::string name) override;
	std::string GetName() const override;
	misLandmarkListTypdef GetLandMarkPoints() override;
	bool SetLandMarkPoints(misLandmarkListTypdef landMarkPoints) override;
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> GetCSCorrelationManager() const override;
	void SetCSCorrelationManager(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> val) override;
	MisObjectType GetObjectType() const override;
	misShortImageViewingStrct GetImageDataProperties(misUID objectUID) override;
	misShort3DModelViewingStrct Get3DModelDataProperties(misUID objectContainerUID, misUID objectUID) override;
	misShortPlanningViewingStruct GetPlanDataProperties(misUID objectUID) override;
	int GetNumberOfImages() const override;
	int GetNumberOf3DModels() override;
	size_t GetNumberOfPlanes() const override;
	std::shared_ptr<IImage> GetMainImage() const override;
	std::vector<std::shared_ptr<IImage>> GetImages() const override;
	misUID GetMainImageUID() const override;
	std::shared_ptr<ICompeleteImageDependencies> GetMainImageProperites() const override;
	ImageDependencyListTypes GetImageDataDependencies() const override;
	ImageContainedPolydataDependencyListTypes GetImageContainedPolydataDependencies() const override;
	PolyDataDependencyListTypes GetPolyDataDependencies() const override;
	VolumeDataDependencyListTypes GetVolumeDataDependencies() const override;
	std::shared_ptr<PlanDataListDependencyTypedef> GetPlanDataDependencies() override;
	misLandMarkBase* GetLandMarkPointer() override;
	void SetObjectVisibility(misUID objectContainerUID, misUID objectUID, bool isVisible,
		misPresentationDimension presentationDim) override;
	void SetObjectOpacity(misUID objectContainerUID, misUID objectUID, double opacity) override;
	misResultCode::ResultIds SetObjectColor(misUID objectUID, misColorStruct color) override;
	misResultCode::ResultIds SetImagedataOpacity(misUID objectUID, double opacity) override;
	void SetImagedataVisibility(misUID objectUID, bool visible) override;
	misResultCode::ResultIds SetImageContainedPolyData(misUID mianImageUID) override;
	misResultCode::ResultIds SetMarginAlaram(misUID containerUID, misUID SegmentedObjectUID, bool val) override;
	void SetImageToRelatedImageDataDependancy(std::shared_ptr<IImage> image) override;
	misResultCode::ResultIds AddNextImageContainedPolydata(misUID pImageData, misUID parentImageUID) override;
	misResultCode::ResultIds AddNextPolydata(misUID pPolydata, misUID parrentImageUID) override;
	misResultCode::ResultIds AddNextVolumedata(
		misUID pVolumedata, misUID parrentImageUID, misObjectVisibilityMap visibleParts) override;
	misResultCode::ResultIds AddNextSegmentedData(misUID objectContainer, misUID parentImageUID, misObjectVisibilityMap)
		override;
	misResultCode::ResultIds UpdateVolumedata(misUID pVolumedata, misObjectVisibilityMap visibleParts) override;
	misResultCode::ResultIds AddNextImageContainedPolydata(
		std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> imageDataDependency) override; //
	misResultCode::ResultIds AddNextPolydata(misCompeletePolyDataDependensiesStrct polydataDependency) override;
	misResultCode::ResultIds AddNextVolumedata(
		std::shared_ptr<IVolumeDataDependency> volumedataDependency) override;
	void DeleteAllLandmarks() override;
	bool Delete3DModel(misUID objectContainerUID, misUID ObjectUID) override;
	misResultCode::ResultIds DeleteVolumedata(misUID volumeDataUID) override;
	void DeleteAllVolumedatas() override;
	misResultCode::ResultIds DeleteSegmentedObject(misUID segmentedObjUID, misUID objectContainerUID) override;
	misResultCode::ResultIds DeleteRenderingObject(misUID renderedUID, misUID volumedataUID) override;
	misResultCode::ResultIds DeletePlanData(misUID planDataUID) override;
	misResultCode::ResultIds UpdateImageContainedPolyDataSDataPointer(ImageContainedPolyDataListTypedef imagePointerList)
		override;
	misResultCode::ResultIds UpdateImageSDataPointer(ImageListTypedef imagePointerList) override;
	misResultCode::ResultIds UpdateVolumeSDataPointer(VolumeDataListTypedef* volumeDataPointerList) override;
	MisObjectType FindObjectType(misUID objectUID) override;
	misResultCode::ResultIds ResetPackage() override;
	misResultCode::ResultIds InvisibleAllPlanDatas() override;
	misResultCode::ResultIds ShowMarginRegion(misUID containerUID, misUID SegmentedObjectUID, bool val) override;
	misResultCode::ResultIds SetImageDataDependencies(const ImageDependencyListTypes& imageDataSDependencies) override;
	misResultCode::ResultIds SetImageContainedPolyDataDependencies(
		ImageContainedPolydataDependencyListTypes imageDataSDependencies) override;
	void SetVolumeDataDependencies(VolumeDataDependencyListTypes volumeDataSDependencies) override;
	misResultCode::ResultIds SetPolyDataDependencies(PolyDataDependencyListTypes* polydataSDependencies) override;
	std::vector<itk::Point<double, 3>> GetParametricSpline() const override;
	void SetParametricSpline(const std::vector<itk::Point<double, 3>>& val) override;
	void CreateVolumeFromImage(std::shared_ptr<IImage> image, double threshold, misApplicationType appType) override;
	std::shared_ptr<PlanDataListTypedef> ExtractPlansListFromPackage() override;

protected:
 
	static std::shared_ptr<misSimpleDataPackage> NewEmptyDataPackage();
	virtual bool FindUsability(misUID parrentImageUID);
	void UpdateVolumesParrentImagePointer();
	misResultCode::ResultIds DeletePolydata(misUID polydataUID);
	misResultCode::ResultIds DeleteImageContainedPolyData(misUID imageContainedPolyDataUID); //
	virtual misResultCode::ResultIds AddingValidityStatus(misUID newObjectParrentUID);

	bool m_ForcedPackageUseability = false; // Note: use when external transform force for usability
	bool m_NaturalPackageUsability = false; // Note :update on primary image confirmation
	MisObjectType m_ObjectType;
	misPackageViewingItemsStrct m_PackageViweingStrct;
	ImageDependencyListTypes m_ImageDataS;
	ImageContainedPolydataDependencyListTypes m_ImageContaineds;
	PolyDataDependencyListTypes* m_PolydataS;
	VolumeDataDependencyListTypes m_VolumeDataS;
	misLandMarkBase* m_LandMark;
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CSCorrelationManager;

private:

	void AddNextImageData(std::shared_ptr<IImage> image);
	bool IsImageType(misUID& objectUID) const;
	bool IsVolumeType(misUID& objectUID);
	bool IsPlanType(misUID& objectUID);
	bool IsPolyDataType(misUID& objectUID);
	bool IsSegmentedType(misUID& objectUID);
	misResultCode::ResultIds SetPolydataVisibility(misUID objectContainerUID, misUID objectUID, bool isVisible,
		misPresentationDimension presentationDim);
	misResultCode::ResultIds SetVolumedataVisibility(misUID objectContainerUID, misUID objectUID, bool isVisible,
		misPresentationDimension presentationDim);
	misResultCode::ResultIds SetPlandataVisibility(misUID objectContainerUID, misUID objectUID, bool visible,
		misPresentationDimension presentationDim);
	misResultCode::ResultIds SetPolydataOpacity(misUID objectContainerUID, misUID objectUID, double opacity);
	misResultCode::ResultIds SetVolumedataOpacity(misUID objectContainerUID, misUID objectUID, double opacity);
	misResultCode::ResultIds SetPlandataOpacity(misUID objectContainerUID, misUID objectUID, double opacity);
	misResultCode::ResultIds SetPolydataColor(misUID objectUID, misColorStruct color);
	misResultCode::ResultIds SetVolumedataColor(misUID objectUID, misColorStruct color);
	misResultCode::ResultIds SetPlandataColor(misUID objectUID, misColorStruct color);
	misVolumeViewingTypes GetDefultVolumeViewingType(misImageDataModality modality, misApplicationType appType);
	std::string GetFlyzoneStatus(const double* position);
	std::string m_Name;
	misUID m_DataObjectUID;
	int m_UIDSetOccurance;

	std::vector<itk::Point<double, 3>> m_ParametricSpline; // See SetParametricSpline
	misUID m_LastSelectedPlanId;
	std::shared_ptr<parcast::IPackagePlanRelRepo> m_PackagePlanRelRepo;
	std::unique_ptr<IVolumeFactory> m_VolumeFactory = std::make_unique<VolumeFactory>();
	
};

typedef std::vector<std::shared_ptr<ISimpleDataPackage>> PackagesListTypedef;