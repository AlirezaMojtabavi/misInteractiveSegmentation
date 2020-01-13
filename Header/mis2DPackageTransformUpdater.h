#pragma once
#include "ISimpleDataPackage.h"
#include "misPlaneContrast.h"
#include "IPackageTransformUpdater.h"
#include "misPlanarRepresentation.h"
#include "IVolumeSlicer.h"
#include "ImageBoundingMerger.h"

class mis2DPackageTransformUpdater : public IPackageTransformUpdater
{
public:
	mis2DPackageTransformUpdater(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManger, 
		std::shared_ptr<IVolumeSlicer>  viewer);
	 void UpdateRepresentationTransforms()  override;
	 void SetSceneReferenceAndPackge(misUID val, std::shared_ptr<ISimpleDataPackage> package) override;

private:
	 misUID GetRefrenceId() const;
	 void UpdateImageTransform(std::shared_ptr<I2DRepresetation> gpurep, misUID referenceImage);
	void SetImageTransformMatrix(misPlaneEnum sourcePlane, misPlaneEnum targetPlane, vtkTransform* trnsf);

	std::shared_ptr<IVolumeSlicer>  m_viewer;
	std::weak_ptr<ISimpleDataPackage> m_Package;
	misUID m_SceneReferenceUID;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CoordianteSystemCorrelationManager;
};

