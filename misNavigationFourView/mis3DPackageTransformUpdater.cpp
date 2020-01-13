#include "stdafx.h"
#include "mis3DPackageTransformUpdater.h"
#include "misPlanarRepresentation.h"
#include "misMathUtils.h"
#include "misImageToTextureMap.h"
#include "IVolumeRepresentation.h"
#include "ICornerProperties.h"

mis3DPackageTransformUpdater::mis3DPackageTransformUpdater(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManger,
	std::shared_ptr<IVolume3DRenderer> viewer)
	: m_viewer(viewer),
	m_CoordianteSystemCorrelationManager(correlationManger)
{
}

void mis3DPackageTransformUpdater::UpdateRepresentationTransforms()
{
	auto referenceImage = GetRefrenceId();
	UpdateVolumeTrasform(referenceImage);
}

 
void mis3DPackageTransformUpdater::SetSceneReferenceAndPackge(misUID val, std::shared_ptr<ISimpleDataPackage> package)
{
	m_SceneReferenceUID = val;
	m_Package = package;
}

 

void mis3DPackageTransformUpdater::UpdateVolumeTrasform(misUID referenceImage)
{
	auto volume = std::dynamic_pointer_cast<IvolumeRepresentation>(m_viewer->GetMainRepresentation());
	if (!volume)
		return;
	volume->UpdateInternalTransforms(m_CoordianteSystemCorrelationManager, referenceImage);
}


misUID mis3DPackageTransformUpdater::GetRefrenceId()const
{
	const auto package = m_Package.lock();
	if (!package)
		return "";
	misUID referenceImage = m_SceneReferenceUID.empty() ? package->GetMainImage()->GetUID() : m_SceneReferenceUID;
	return referenceImage;
}

