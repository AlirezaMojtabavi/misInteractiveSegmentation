#include "stdafx.h"
#include "misBoneSkineVolume.h"
#include "misDataSetManager.h"
#include "misVolumeThresholdSetting.h"
#include "misVolumeDataDependensies.h"
#include "misVolumeData.h"
#include "misVolumeViewingTypes.h"

misBoneSkineVolume::misBoneSkineVolume()
	:m_VolumeData(std::make_shared<misVolumeDataDependensies>())
{
	m_VolumeData->SetVolume(std::make_shared<misVolumeData>());
	m_VolumeData->SetVisibilityIn2D(true);
	m_VolumeData->GetVolume()->SetRenderingType(misVolumeRendering);
	m_VolumeData->SetAutomaticallyCreated(false);
}

void misBoneSkineVolume::SetImage(std::shared_ptr<IImage> image)
{
	m_Image = image;
	m_VolumeData->SetImage(image);
	m_VolumeData->GetVolume()->SetParentImageUID(image->GetUID());
	m_VolumeData->SetParentImageUID(image->GetUID()) ;
	m_VolumeData->GetVolume()->SetImageModality(image->GetImageModality());
}

void misBoneSkineVolume::SetMinThreshold(const mis3DModelTypes obJcetType, const double threshold)
{
	m_VolumeData->GetVolume()->SetMinThreshold(GetVolumeViewingtype(obJcetType), threshold);
	misObjectVisibilityPair newVolumeRow;
	newVolumeRow.first = m_VolumeData->GetVolume()->GetObjectUID(GetVolumeViewingtype(obJcetType));
	_ASSERT(!newVolumeRow.first.empty());
	m_VolumeData->SetObjectVisibilityProperties(newVolumeRow.first, newVolumeRow.second);
	m_OriginalVolumeMap = m_VolumeData->GetAllObjectVisibility();
	MergeVolumeDataRepresentation();
}

std::shared_ptr<IVolumeDataDependency> misBoneSkineVolume::GetVolumeData() const
{
	return m_VolumeData;
}

misUID misBoneSkineVolume::GetVolumeUID()const
{
	return  m_VolumeData->GetVolume()->GetUID();
}

misUID misBoneSkineVolume::GetVolumeViewingTypeUID(const mis3DModelTypes obJcetType)
{
	return m_VolumeData->GetVolume()->GetObjectUID(GetVolumeViewingtype(obJcetType));
}

misObjectVisibilityMap misBoneSkineVolume::GetVisibiltyMap()
{
	return m_VolumeData->GetAllObjectVisibility();
}

void misBoneSkineVolume::MergeVolumeDataRepresentation()
{
	for (auto mapIter = m_OriginalVolumeMap.begin(); mapIter != m_OriginalVolumeMap.end(); mapIter++)
	{
		mis3DModelObjectOpacityPropertiesStrct modelProp;
		bool found = m_VolumeData->GetObjectVisibilityProperties(mapIter->first, modelProp);
		if (!found)
		{
			m_VolumeData->SetObjectVisibilityProperties(mapIter->first, mapIter->second);
		}
	}
	m_OriginalVolumeMap = m_VolumeData->GetAllObjectVisibility();
}

void misBoneSkineVolume::SetObjectName(misVolumeViewingTypes objectType, std::string name)
{
	m_VolumeData->GetVolume()->SetObjectName(objectType, name);
}

void misBoneSkineVolume::AddToCoordinateSystem()
{
	if (!m_VolumeData->GetParentImageUID().empty())
	{
		misDatasetManager::GetInstance()->AddCoordinateSystem(m_VolumeData->GetVolume());
		MergeVolumeDataRepresentation();
	}
}

void misBoneSkineVolume::UpdateVolumeRedeingSceneBasedOnNormalizedThreshold(mis3DModelTypes objectType,
	misVolumeViewingTypes ObjectVolumeViewing, double normalizedThreshold)
{
	misVolumeThresholdSetting imageThreshold(m_Image);
	double threshold = imageThreshold.GetObjectThresholdBasedNormalizedThreshold(objectType, normalizedThreshold);
	if (m_VolumeData->GetVolume()->GetObjectUID(ObjectVolumeViewing) != "")
	{
		double previousThreshold = m_VolumeData->GetVolume()->GetMinThreshold(ObjectVolumeViewing);
		if (previousThreshold != threshold)
		{
			m_VolumeData->GetVolume()->SetMinThreshold(ObjectVolumeViewing, threshold);;
		}
	}
}

double misBoneSkineVolume::GetPreviosThreshold(misVolumeViewingTypes ObjectVolumeViewing ) 
{
	 return  m_VolumeData->GetVolume()->GetMinThreshold(ObjectVolumeViewing);
}

void misBoneSkineVolume::UpdateHeadRestRenderingBasedOnNormalizedThreshold(mis3DModelTypes objectType,
	misVolumeViewingTypes ObjectVolumeViewing, double normalizedThreshold)
{
	misVolumeThresholdSetting imageThreshold(m_Image);
	double threshold = imageThreshold.GetObjectThresholdBasedNormalizedThreshold(objectType, normalizedThreshold);
	auto  previousThreshold = GetPreviosThreshold(ObjectVolumeViewing);
	if (previousThreshold != threshold)
	{
		m_VolumeData->GetVolume()->SetMinThreshold(ObjectVolumeViewing, threshold);
	}
}

void misBoneSkineVolume::HideCurrenVolume()
{
	m_VolumeData->SetAllObjectVisibility(false);
}

void misBoneSkineVolume::ShowAllVolume()
{
	m_VolumeData->SetAllObjectVisibility(true);
}

void misBoneSkineVolume::SetColorMapTransferFunction(std::shared_ptr<TransFuncIntensity> transfunc)
{
	m_VolumeData->SetTransferFunction(transfunc);
}

misVolumeViewingTypes misBoneSkineVolume::GetVolumeViewingtype(const mis3DModelTypes obJcetType)const
{
	misVolumeViewingTypes volumeViewingType;
	if (misSkin == obJcetType)
	{
		volumeViewingType = misVolumeViewingTypes::misSkinviewing;
	}
	else if (misBone == obJcetType)
	{
		volumeViewingType = misVolumeViewingTypes::misBoneViwing;
	}
	else if (misMetal == obJcetType)
	{
		volumeViewingType = misVolumeViewingTypes::misMetalViewing;
	}
	else
	{
		volumeViewingType = misVolumeViewingTypes::misAllViewing;
	}
	return volumeViewingType;
}
