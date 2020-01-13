#include "stdafx.h"
#include "mis2DPackageTransformUpdater.h"
#include "misPlanarRepresentation.h"
#include "misMathUtils.h"
#include "misImageToTextureMap.h"
#include "IVolumeRepresentation.h"
#include "ICornerProperties.h"

mis2DPackageTransformUpdater::mis2DPackageTransformUpdater(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManger,

	std::shared_ptr<IVolumeSlicer> viewer)
	:m_viewer(viewer),
	m_CoordianteSystemCorrelationManager(correlationManger)
{
}

void mis2DPackageTransformUpdater::UpdateRepresentationTransforms()
{
	auto referenceImage = GetRefrenceId();
	auto imageRep = m_viewer->GetImageRprensentaion();
	if (imageRep)
		UpdateImageTransform(imageRep, referenceImage);

}

void mis2DPackageTransformUpdater::UpdateImageTransform(std::shared_ptr<I2DRepresetation> gpurep,
                                                        misUID referenceImage)
{
	auto firstImageUID = gpurep->GetImageUID(FirstImage);
	auto secondImageUID = gpurep->GetImageUID(SecondImage);
	auto image1 = gpurep->GetImage(FirstImage);
	auto image2 = gpurep->GetImage(SecondImage);
	if (referenceImage == firstImageUID)
	{
		auto transform = m_CoordianteSystemCorrelationManager->GetTransform(referenceImage, secondImageUID);
		if (transform->IsValid())
		{
			auto vtkTrans = misMathUtils::CreateVtkTransform(transform->GetTransform());
			SetImageTransformMatrix(FirstImage, SecondImage, vtkTrans);
		}
	}
	else if (referenceImage == secondImageUID)
	{
		auto transform = m_CoordianteSystemCorrelationManager->GetTransform(referenceImage, firstImageUID);
		if (transform->IsValid())
		{
			auto vtkTrans = misMathUtils::CreateVtkTransform(transform->GetTransform());
			SetImageTransformMatrix(SecondImage, FirstImage, vtkTrans);
		}
	}
}

void mis2DPackageTransformUpdater::SetSceneReferenceAndPackge(misUID val, std::shared_ptr<ISimpleDataPackage> package)
{
	m_SceneReferenceUID = val;
	m_Package = package;
}

void mis2DPackageTransformUpdater::SetImageTransformMatrix(misPlaneEnum sourcePlane, misPlaneEnum targetPlane, vtkTransform* trnsf)
{
	auto gpu2DRep = m_viewer->GetImageRprensentaion();
	gpu2DRep->ApplyTransformToScene(sourcePlane, targetPlane, trnsf);
}

misUID mis2DPackageTransformUpdater::GetRefrenceId()const
{
	const auto package = m_Package.lock();
	if (!package)
		return "";
	misUID referenceImage = m_SceneReferenceUID.empty() ? package->GetMainImage()->GetUID() : m_SceneReferenceUID;
	return referenceImage;
}