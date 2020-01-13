#include "ISimpleDataPackage.h"
#include "IPackagePlanRelRepo.h"
#include "misPackageViewingItemsStrct.h"
#include "IPackageViewingExtractor.h"

class misPackageViewingExtractor : public IPackageViewingExtractor
{
public:
	explicit misPackageViewingExtractor(std::shared_ptr<const ISimpleDataPackage> packge,
		std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo);

	misPackageViewingItemsStrct GetViewingPart() const override
	{
		return m_PackageViweingStrct;
	}
private:

	void UpdateImageViewingParts();
	void UpdateImageContainedPolyDataParts();
	void UpdateVolumeViewingParts();
	void UpdatePlansViewingParts();
	void Update();
	std::weak_ptr<const ISimpleDataPackage> m_Packge;
	std::weak_ptr<parcast::IPackagePlanRelRepo> m_PackagePlanRelRepo;
	misPackageViewingItemsStrct  m_PackageViweingStrct;

};
