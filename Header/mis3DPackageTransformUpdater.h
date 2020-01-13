#pragma once
#include "IPackageTransformUpdater.h"
 
#pragma once
#include "ISimpleDataPackage.h"
#include "misPlaneContrast.h"
#include "IPackageTransformUpdater.h"
#include "IVolume3DRenderer.h"
#include "misPlanarRepresentation.h"

class mis3DPackageTransformUpdater : public IPackageTransformUpdater
{
public:
	mis3DPackageTransformUpdater(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManger,
		 std::shared_ptr<IVolume3DRenderer>  viewer	);
	void UpdateRepresentationTransforms()  override;
	void SetSceneReferenceAndPackge(misUID val, std::shared_ptr<ISimpleDataPackage> package) override;
	misUID GetRefrenceId() const override;

private:

	void UpdateVolumeTrasform(misUID referenceImage);
	std::shared_ptr<IVolume3DRenderer>  m_viewer;
	std::weak_ptr<ISimpleDataPackage> m_Package;
	misUID m_SceneReferenceUID;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CoordianteSystemCorrelationManager;
};

