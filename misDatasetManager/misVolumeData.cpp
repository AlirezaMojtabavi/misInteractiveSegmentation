#include "StdAfx.h"
#include "misVolumeData.h"

#include "misApplicationSetting.h"
#include "misEnums.h"
#include "misStringTools.h"
#include "IVolumeRenderingColorMaps.h"
#include "misColormapGeneratorFactory.h"
#include "misImageDataProperties.h"
#include "IImage.h"
#include "misStrctVolumeData.h"
#include "misStrctColorData.h"

using namespace std;

misVolumeData::misVolumeData()
	:m_Image(NULL)
{
	SetAmbient(0.1);
	SetDiffuse(0.3);
	SetSpecular(0.25);
	Reset();
	m_ObjectType = misVolumeDataType;
	m_DataObjectUID = misStringTools::GenerateNewUID();
	m_RenderingType = misVolumeRendering;
	m_VolumesProperties.clear();
}

void misVolumeData::ResetProperties(void)
{
	m_ViewingModificationFlag = true;
	m_MisImageFlag = false;
	m_OpacityColorMappingFinal.clear();
	m_ScalarType = -1;
	m_ViewAllObjectsOpacity = -1;
}

void misVolumeData::SetImage(std::shared_ptr<IImage> image)
{
	if (!image)
		return;
	m_Image = image;
	m_ScalarType = image->GetScalarType();
	misImageDataProperties* imageProperty = image->GetImageDataProperties();
	m_ImageModality = imageProperty->imagingProprties.ImageModality;
	m_MisImageFlag = true;
	m_ComponentHasBeenChanged = true;
	m_ParentImageUID = image->GetUID();
}

void misVolumeData::DeepCopy(IVolumeData *src)
{
	auto right = dynamic_cast<misVolumeData*>(src);
	m_ParentImageUID = right->m_ParentImageUID;
	m_MisImageFlag = right->m_MisImageFlag;

	m_Specular = right->m_Specular;
	m_Ambient = right->m_Ambient;
	m_Diffuse = right->m_Diffuse;

	m_ImageModality = right->m_ImageModality;
	m_ScalarType = right->m_ScalarType;

	m_VolumesProperties = right->m_VolumesProperties;

	//m_ViewSomeObjectsProp     = src->m_ViewSomeObjectsProp;
	m_ViewAllObjectsOpacity = right->m_ViewAllObjectsOpacity;

	m_ViewingModificationFlag = true;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::CheckObjectUID(misVolumeRangeColor& volumeComponentProperties)
{
	if (volumeComponentProperties.objectUID == "")
	{
		volumeComponentProperties.objectUID = misStringTools::GenerateNewUID();
	}
}
void misVolumeData::SetObjectColor(misVolumeViewingTypes objectType, misColorStruct ObjectColor)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp = GetObjectProperties(objectType);

	objectProp.volumeColor = ObjectColor;
	objectProp.AutomaticColorMode = false;

	m_VolumesProperties[objectType] = objectProp;

	m_ComponentHasBeenChanged = true;
}

misColorStruct misVolumeData::GetObjectColor(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		misColorStruct tempColor;
		tempColor.InVisible();
		return tempColor;
	}
	misVolumeRangeColor objectProp;
	objectProp = m_VolumesProperties[objectType];

	return objectProp.volumeColor;
}

void misVolumeData::UsedDefaultObjectColor(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp = m_VolumesProperties[objectType];
	objectProp.volumeColor.Reset();
	objectProp.AutomaticColorMode = true;

	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::SetMinThreshold(misVolumeViewingTypes objectType, double minThreshold)
{
	misVolumeRangeColor objectProp;
	objectProp = GetObjectProperties(objectType);
	objectProp.minThreshold = minThreshold;
	objectProp.UsedDeafultThreshold = false;

	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::SetMinMaxThreshold(misVolumeViewingTypes objectType, double minThreshold, double maxThreshold)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp = GetObjectProperties(objectType);

	objectProp.minThreshold = minThreshold;
	objectProp.UsedDeafultThreshold = false;

	objectProp.maxThreshold = maxThreshold;
	objectProp.UsedDeafultMaxThreshold = false;

	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;


}

double misVolumeData::GetMinThreshold(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return 0;
	}
	misVolumeRangeColor objectProp;
	objectProp = m_VolumesProperties[objectType];
	return objectProp.minThreshold;
}

void misVolumeData::UsedDefaultThreshold(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp = m_VolumesProperties[objectType];
	objectProp.minThreshold = -1;

	objectProp.UsedDeafultThreshold = true;
	objectProp.UsedDeafultMaxThreshold = true;

	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::UsedDefaultThresholdForAll(void)
{
	misVolumeComponentPropTypdef::iterator iter;
	misVolumeRangeColor objectProp;

	for (iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		(*iter).second.minThreshold = -1;
		(*iter).second.UsedDeafultThreshold = true;
	}
	m_ComponentHasBeenChanged = true;
}

misVolumeRangeColor misVolumeData::GetObjectProperties(misVolumeViewingTypes objectType)
{
	misVolumeRangeColor objectProp;

	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return objectProp;
	}
	// if the object does not exist the UID will empty

	misVolumeComponentPropTypdef::iterator iter;
	iter = m_VolumesProperties.find(objectType);
	if (iter != m_VolumesProperties.end())
	{
		objectProp = (*iter).second;
	}
	else
	{
		CheckObjectUID(objectProp);
		misVolumeComponentPair newVol;
		newVol.first = objectType;
		newVol.second = objectProp;
		m_VolumesProperties.insert(newVol);
	}
	return objectProp;
}

std::string misVolumeData::GetParentImageUID() const
{
	return m_ParentImageUID;
}

void misVolumeData::SetParentImageUID(std::string val)
{
	m_ParentImageUID = val;
}

void misVolumeData::SetObjectName(misVolumeViewingTypes objectType, string name)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		//_ASSERT( 0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp = GetObjectProperties(objectType);
	objectProp.Name = name;

	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;
}

std::string misVolumeData::GetObjectName(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return "";
	}
	misVolumeRangeColor objectProp;
	objectProp = m_VolumesProperties[objectType];

	return objectProp.Name;
}

void misVolumeData::AddNewObject(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	misVolumeRangeColor objectProp;
	objectProp.UsedDeafultThreshold = true;
	objectProp.AutomaticColorMode = true;

	// TODO: check
	m_VolumesProperties[objectType] = objectProp;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::DeleteObject(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
	{
		_ASSERT(0 == 1);
		return;
	}
	m_VolumesProperties.erase(objectType);
	m_ComponentHasBeenChanged = true;
}

misDoubleColorListTypedef misVolumeData::GetOpacityColorMap(misPresentationDimension presentationDim)
{
	if (m_ComponentHasBeenChanged)
		ConvertVolumePropToColorKeys(presentationDim);

	return m_OpacityColorMappingFinal;
}

void misVolumeData::ConvertVolumePropToColorKeys(misPresentationDimension presentationDim)
{
	m_OpacityColorMappingFinal.clear();
	for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		auto objectType = (*iter).first;
		auto objectProp = (*iter).second;
		bool check2D = (objectProp.visibilityProp.visibilityIn2DScene && presentationDim == twoDimension);
		bool check3D = (objectProp.visibilityProp.GetVisibilityIn3DScene() && presentationDim == threeDimension);
		if (check2D || check3D)
		{
			misColormapGeneratorFactory colormapFactory;
			std::shared_ptr<IVolumeRenderingColorMaps> colorMapTables;
			auto appType = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
			if (appType == AnimalImaging)
				colorMapTables = colormapFactory.createColormapType(AnimalImagingColormap);
			else if (appType == Dental)
				colorMapTables = colormapFactory.createColormapType(DentalColormap);
			else
				colorMapTables = colormapFactory.createColormapType(OtherColormap);
			if (!colorMapTables)
				return;

			colorMapTables->SetImageModality(m_ImageModality);
			colorMapTables->SetObjectType(objectType);

			if (!objectProp.UsedDeafultThreshold)
				colorMapTables->SetObjectThreshold(objectProp.minThreshold);
			else
				colorMapTables->SetObjectThresholdDefault();

			if (!objectProp.AutomaticColorMode)
				colorMapTables->SetObjectColor(objectProp.volumeColor);
			else
				colorMapTables->SetObjectColorDefault();

			misColorListTypedef objectColorMap = colorMapTables->GetVolumeColorMap();

			// set the final color has been used  : note must call after GetVolumeColorMap
			if (appType != Dental)
				(*iter).second.volumeColor = colorMapTables->GetObjectColor();
			FillFinalColorMap(objectColorMap, objectProp.visibilityProp.OpacityIn3DScene);
		}
	}
	m_ComponentHasBeenChanged = false;
}

void misVolumeData::FillFinalColorMap(misColorListTypedef objectColorMap, double opacity)
{
	for (auto iter = objectColorMap.begin(); iter != objectColorMap.end(); iter++)
	{
		misDoubleColorStruct  finalColor;
		finalColor.Red = float(iter->second.red) / 255.0;
		finalColor.Green = float(iter->second.green) / 255.0;
		finalColor.Blue = float(iter->second.blue) / 255.0;
		finalColor.Alpha = double(iter->second.alpha) * opacity;

		double GL = iter->first;
		m_OpacityColorMappingFinal[GL] = finalColor;
	}
}

void misVolumeData::SetViewableObjectsAll(double opacity)
{
	if (opacity < 0)
		opacity = 0;
	else if (opacity > 1)
		opacity = 1;

	m_ViewAllObjectsOpacity = opacity;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::SetViewableObjectsDefault(void)
{
	m_ViewAllObjectsOpacity = -1;
	m_ComponentHasBeenChanged = true;
}

bool misVolumeData::IsExistObject(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
		return false;

	for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		if ((*iter).first == objectType)
			return true;
	}
	return false;
}

int misVolumeData::GetObjectsNumber(void)
{
	return m_VolumesProperties.size();
}

misVolumeComponentPropTypdef misVolumeData::GetColormaps(void)
{
	return m_VolumesProperties;
}


misVolumeViewingTypes misVolumeData::GetObjectType(misUID objectUID)
{
	if (objectUID == "")
		return misVolumeViewingTypes::UnsetViewingType;

	for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		if ((*iter).second.objectUID == objectUID)
			return (*iter).first;
	}
	return misVolumeViewingTypes::UnsetViewingType;
}

misUID misVolumeData::GetObjectUID(misVolumeViewingTypes objectType)
{
	if (misVolumeViewingTypes::UnsetViewingType == objectType)
		return "";
	for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		if (iter->first == objectType)
		{
			_ASSERT((*iter).second.objectUID != "");
			return (*iter).second.objectUID;
		}
	}
	return "";
}

void misVolumeData::Reset(void)
{
	ResetProperties();
	m_VolumesProperties.clear();
	m_ComponentHasBeenChanged = true;
}

mis3DModelRenderingType misVolumeData::GetRenderingType()
{
	return m_RenderingType;
}

void misVolumeData::SetRenderingType(mis3DModelRenderingType type)
{
	m_RenderingType = type;
}

void misVolumeData::SetColormaps(misVolumeComponentPropTypdef volumeComponentPropertyList)
{
	m_VolumesProperties = volumeComponentPropertyList;
	m_ComponentHasBeenChanged = true;
}

void misVolumeData::SetImageModality(misImageDataModality modality)
{
	if (modality)
		m_ImageModality = modality;
}

misImageDataModality misVolumeData::GetImageModality() const
{
	return m_ImageModality;
}

void misVolumeData::SetComponentVisiblityByMap(misObjectVisibilityMap visibilityMap)
{
	if (visibilityMap.size())
	{
		SetAllComponentsVisibilityOFF();

		for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
		{
			misVolumeViewingTypes ObjectType = (*iter).first;
			misUID compUID = (*iter).second.objectUID;
			misVolumeRangeColor componentProp = (*iter).second;
			auto mapIter = visibilityMap.find(compUID);
			if (mapIter != visibilityMap.end())
			{
				mis3DModelObjectOpacityPropertiesStrct mapProp = (*mapIter).second;
				componentProp.visibilityProp.visibilityIn2DScene = mapProp.visibilityIn2DScene;
				componentProp.visibilityProp.SetVisibilityIn3DScene(mapProp.GetVisibilityIn3DScene());
				componentProp.visibilityProp.SetOpacityIn2DScene(mapProp.GetOpacityIn2DScene());
				componentProp.visibilityProp.OpacityIn3DScene = mapProp.OpacityIn3DScene;
				m_VolumesProperties[ObjectType] = componentProp;
			}
		}
	}
}

void misVolumeData::SetAllComponentsVisibilityOFF()
{
	for (auto iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		misVolumeViewingTypes ObjectType = (*iter).first;
		misUID compUID = (*iter).second.objectUID;
		misVolumeRangeColor componentProp = (*iter).second;
		componentProp.visibilityProp.visibilityIn2DScene = false;
		componentProp.visibilityProp.SetVisibilityIn3DScene(false);
		componentProp.visibilityProp.SetOpacityIn2DScene(0);
		componentProp.visibilityProp.OpacityIn3DScene = 0;
		m_VolumesProperties[ObjectType] = componentProp;
		m_ComponentHasBeenChanged = true;
	}
}

void misVolumeData::SetComponentVisibilityAll()
{
	misVolumeComponentPropTypdef::iterator iter;
	for (iter = m_VolumesProperties.begin(); iter != m_VolumesProperties.end(); iter++)
	{
		misVolumeViewingTypes ObjectType = (*iter).first;
		misUID compUID = (*iter).second.objectUID;
		misVolumeRangeColor componentProp = (*iter).second;
		componentProp.visibilityProp.Reset();
		m_VolumesProperties[ObjectType] = componentProp;
	}

	m_ComponentHasBeenChanged = true;
}

void misVolumeData::ChangeComponentOpacity(misVolumeViewingTypes componentType, double opacity)
{
	if (misVolumeViewingTypes::UnsetViewingType == componentType)
	{
		_ASSERT(0 == 1);
		return;
	}
	if (!m_VolumesProperties.empty())
	{
		misVolumeComponentPropTypdef::iterator Tempcomponent = m_VolumesProperties.find(componentType);
		if (Tempcomponent != m_VolumesProperties.end())
		{
			Tempcomponent->second.visibilityProp.SetOpacityIn2DScene(1.0);
			Tempcomponent->second.visibilityProp.OpacityIn3DScene = opacity;
			m_ComponentHasBeenChanged = true;
		}
	}
}

std::string misVolumeData::GetUID() const
{
	return m_DataObjectUID;
}

void misVolumeData::SetUID(const std::string& id)
{
	m_DataObjectUID = id;
}

std::shared_ptr<IImage> misVolumeData::GetIamge() const
{
	return m_Image;
}