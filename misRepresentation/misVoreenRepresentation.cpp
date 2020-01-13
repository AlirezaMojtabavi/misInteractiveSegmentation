#include "StdAfx.h"
#include "misVoreenRepresentation.h"

#include "misImageToTextureMap.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misImageToVolumeHandel.h"
#include "misOpenglTexture.h"
#include "misRepresentation.h"
#include "misTexturePropertyStruct.h"
#include "misDebug.h"
#include "misMathUtils.h"

using std::map;
using std::pair;
using std::string;

misVoreenRepresentation::misVoreenRepresentation(void) 
	:m_Representation(std::make_shared<misRepresentation>("voreen"))
{
	m_VoreenMapper = vtkSmartPointer<misVoreenCanvasMapper>::New();
	m_VoreenActor = vtkSmartPointer<misVoreenActor>::New();
	m_VoreenActor->SetMapper(m_VoreenMapper);
	m_Representation->AddProp(m_VoreenActor);
	m_Renderer = NULL;
	m_numOfVolume = 0;
	m_WindowSize[0] = 0;
	m_WindowSize[1] = 0;
	m_ToolPosition[0] = 0.0;
	m_ToolPosition[1] = 0.0;
	m_ToolPosition[2] = 0.0;

	this->m_CroppingDir = NotSetCroppingDirection;
}



void misVoreenRepresentation::SetVolume(int id, misOpenglTexture* pTexture)
{
	misImageToVolumeHandel  convertor;
	voreen::VolumeHandle*   handle = convertor.ConvertTexture(pTexture);
	if (handle)
	{
		tgt::vec3 spacing = pTexture->GetTexturePropertyStrct().Spacing;
		handle->getVolume()->setSpacing(spacing);

		if (m_Volumehandles.size() < id + 1)
			m_Volumehandles.resize(id + 1);

		m_Volumehandles[id] = handle;
		string UID = pTexture->getName();
		m_Volumehandles[id]->getVolume()->meta().setUnit(UID);
		m_numOfVolume = m_Volumehandles.size();
		//_ASSERT(m_WindowSize[0]>0);
		//_ASSERT(m_WindowSize[1]>0);
		if (m_Volumehandles.size() == m_TransferFunctions.size())
			this->m_VoreenMapper->SetCanvasPart(m_VolumeHandleMap, m_TextureMap, m_WindowSize);
	}
}


void misVoreenRepresentation::SetVolume(misOpenglTexture* pTexture, ImageContainedTransferFuncs3D pTextureTFs)
{
	if (!pTexture)
		return;
	m_TextureMap[pTexture] = pTextureTFs;
	misImageToVolumeHandel  convertor;
	voreen::VolumeHandle*   handle = convertor.ConvertTexture(pTexture);
	if (!handle)
		return;
	tgt::vec3 spacing = pTexture->GetTexturePropertyStrct().Spacing;
	handle->getVolume()->setSpacing(spacing);
	string UID = pTexture->GetImageUID();
	handle->getVolume()->meta().setUnit(UID);
	m_VolumeHandleMap[pTexture] = handle;
	this->m_VoreenMapper->SetCanvasPart(m_VolumeHandleMap, m_TextureMap, m_WindowSize);
}




void misVoreenRepresentation::SetWindowSize(tgt::ivec3  size)
{
	if (m_WindowSize[0] == size[0] && m_WindowSize[1] == size[1])
		return;
	m_WindowSize = size;
	tgt::ivec2   newSize;
	newSize[0] = size[0];
	newSize[1] = size[1];
	this->m_VoreenMapper->SetWindowSize(newSize);
 }




void misVoreenRepresentation::SetTranformMatrixToVolumes(int id, tgt::mat4 matrix)
{
	m_VoreenMapper->SetTransformToVolume(id, matrix);
	//	this->m_VoreenMapper->SetCanvasPart(m_Tetxurehandles,m_TransferFunctions,m_WindowSize);

}

void misVoreenRepresentation::SetTranformMatrixToVolumes(string name, tgt::mat4 matrix)
{
	m_VoreenMapper->SetTransformToVolume(name, matrix);
}

 

void misVoreenRepresentation::SetToolPosition(double xCoord, double yCoord, double zCoord)
{

	this->m_VoreenMapper->SetToolPosition(xCoord, yCoord, zCoord);
	m_ToolPosition[0] = xCoord;
	m_ToolPosition[1] = yCoord;
	m_ToolPosition[2] = zCoord;
}

void misVoreenRepresentation::SetRenderer(vtkRenderer* val)
{
	m_Renderer = val;
	this->m_VoreenMapper->SetRenderer(val);
}


// std::vector<misOpenglTexture*> misVoreenRepresentation::GetTextures() const
// {
// 	return m_Textures;
// }

void misVoreenRepresentation::SetCroppingDirection(misCroppingDirectionInVR direction)
{
	if (m_ToolPosition[0] == 0 && m_ToolPosition[1] == 0 && m_ToolPosition[2] == 0)
		return;

	m_CroppingDir = direction;
	if (direction == AnteriorDown ||
		direction == AnteriorUp ||
		direction == NoCut)
	{
		this->ClipingOF();
		m_VoreenMapper->SetCropping(direction);
	}
	else
		ClipByPlane(direction);
}

void misVoreenRepresentation::ClipByPlane(misCroppingDirectionInVR direction)
{
	double normal[3];
	switch (direction)
	{
	case AnteriorCut:
	{
		normal[0] = 0;
		normal[1] = 1;
		normal[2] = 0;
		break;
	}
	case SagittalRight:
	{
		normal[0] = -1;
		normal[1] = 0;
		normal[2] = 0;
		break;
	}
	case SagittalLeft:
	{
		normal[0] = 1;
		normal[1] = 0;
		normal[2] = 0;
		break;
	}
	case CoronalUp:
	{
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = -1;
		break;
	}
	case CoronalDown:
	{
		normal[0] = 0;
		normal[1] = 0;
		normal[2] = 1;
		break;
	}
	}
	m_VoreenMapper->SetCropping(direction);
	double d = vtkMath::Dot(m_ToolPosition, normal);
	tgt::vec4 CutPlane = tgt::vec4(normal[0], normal[1], normal[2], d);
	//set cliping plane
	this->ClipingOF();
	this->SetClipingPlane(CutPlane);
	//clipping on
	this->ClipingOn();
}

void misVoreenRepresentation::ClipingOn()
{

	if (m_VoreenMapper)
		m_VoreenMapper->ClipingOn();
}

void misVoreenRepresentation::ClipingOF()
{

	if (m_VoreenMapper)
		m_VoreenMapper->ClipingOF();

}

void misVoreenRepresentation::SetClipingPlane(tgt::vec4 plane)
{
	if (m_VoreenMapper)
		m_VoreenMapper->SetClipingPlane(plane);
}



void misVoreenRepresentation::SetSampleRate(float sampleRate)
{
	if (m_VoreenMapper)
		m_VoreenMapper->SetSampleRate(sampleRate);
}

void misVoreenRepresentation::ClearTextureHnadleMapBeforSetVolume()
{
	m_TextureMap.clear();
	m_VolumeHandleMap.clear();
	m_TransferFunctions.clear();
	m_Volumehandles.clear();
}

void misVoreenRepresentation::ResetMapInShader()
{
	this->m_VoreenMapper->ResetMapInShader();
}

void misVoreenRepresentation::SetROI(const double* fov)
{

	if (m_Volumehandles.size() > 0)
	{
		m_Volumehandles[0]->getVolume()->SetROI(fov);
	}
	else
	{
		map<misOpenglTexture*, voreen::VolumeHandle*>	::iterator existedPair;
		for (existedPair = m_VolumeHandleMap.begin(); existedPair != m_VolumeHandleMap.end(); existedPair++)
		{
			existedPair->second->getVolume()->SetROI(fov);
		}
	}
}

void misVoreenRepresentation::RemoveFOV()
{
	if (m_Volumehandles.size() > 0)
	{
		m_Volumehandles[0]->getVolume()->RemoveFOV();
	}
	else
	{
		map<misOpenglTexture*, voreen::VolumeHandle*>	::iterator existedPair;
		for (existedPair = m_VolumeHandleMap.begin(); existedPair != m_VolumeHandleMap.end(); existedPair++)
		{
			existedPair->second->getVolume()->RemoveFOV();
		}
	}
}

void misVoreenRepresentation::ModifyVolume()
{
	if (this->m_VoreenMapper)
		this->m_VoreenMapper->Modify();
}

void misVoreenRepresentation::CompileVolumeShader()
{
	if (this->m_VoreenMapper)
		this->m_VoreenMapper->CompileVolumeShader(m_VolumeHandleMap.size());
}

void misVoreenRepresentation::RnderProxyGeometry(bool val)
{
	if (m_VoreenMapper)
		this->m_VoreenMapper->RnderProxyGeometry(val);
}

std::vector<voreen::VolumeHandle*> misVoreenRepresentation::GetVolumehandles() const
{
	return m_VoreenMapper->GetVolumeHandles();
}

vtkSmartPointer<misVoreenCanvasMapper> misVoreenRepresentation::GetVoreenMapper() const
{
	return m_VoreenMapper;
}

unsigned long misVoreenRepresentation::AddObserver(const itk::EventObject & event, itk::Command* command)
{
	m_DummyObject->SetRepresenation(shared_from_this());
	return m_DummyObject->AddObserver(event, command);
}

void misVoreenRepresentation::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->InvokeEvent(event);

}

bool misVoreenRepresentation::HasObserver(const itk::EventObject & event) const
{
	return m_DummyObject->HasObserver(event);
}

std::string misVoreenRepresentation::GetObjectName() const
{
	return "misVoreenRepresentation";
}

void misVoreenRepresentation::SetObjectName(std::string val)
{
	
}

void misVoreenRepresentation::SetRepresentationName(std::string name)
{
	m_Representation->SetObjectName(name);
}

void misVoreenRepresentation::AddProp(vtkProp* prop)
{
	m_Representation->AddProp(prop);
}

void misVoreenRepresentation::SetVisibilityOff(void)
{
	m_Representation->SetVisibilityOff();
}

void misVoreenRepresentation::SetVisibility(bool value)
{
	m_Representation->SetVisibility(value);
}

void misVoreenRepresentation::SetVisibilityOn(void)
{
	m_Representation->SetVisibilityOn();
}

int misVoreenRepresentation::GetNumberOfActors()
{
	return m_Representation->GetNumberOfActors();
}

void misVoreenRepresentation::Reset()
{
	m_Representation->Reset();
}
void misVoreenRepresentation::SetPosition(double position[3])
{
	m_Representation->SetPosition(position);
}

void misVoreenRepresentation::SetPosition(double x, double y, double z)
{
	m_Representation->SetPosition(x, y , z);
}

double* misVoreenRepresentation::GetPosition() const
{
	return m_Representation->GetPosition();
}

void misVoreenRepresentation::GetPosition(double position[3])
{
	m_Representation->GetPosition(position);
}

void misVoreenRepresentation::SetUserTransform(vtkTransform *transform)
{
	m_Representation->SetUserTransform(transform);
}

vtkProp* misVoreenRepresentation::GetActor(int index)
{
	return m_Representation->GetActor(index);
}

bool misVoreenRepresentation::CalculatedBoundingBox()
{
	return m_Representation->CalculatedBoundingBox();
}

itk::BoundingBox<double, 3, double>::Pointer misVoreenRepresentation::GetBoundingBox()
{
	return m_Representation->GetBoundingBox();
}

bool misVoreenRepresentation::GetBoundingBox(double *boundingBox)
{
	return m_Representation->GetBoundingBox(boundingBox);
}

IRepresentation::ActorsListType misVoreenRepresentation::GetActors() const
{
	return m_Representation->GetActors();
}

void misVoreenRepresentation::UpdateInternalTransforms(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> transforms, 
	misUID referenceImage)
{
	std::vector<voreen::VolumeHandle*> handles = GetVolumehandles();
	for (auto handle : handles)
	{
		const bool volumeIsSgemented = handle->getVolume()->getTexture()->GetIsPolydataFlag();

		misUID imageUID = volumeIsSgemented ? handle->getVolume()->getTexture()->GetParentimageID()
			: handle->getVolume()->getTexture()->GetImageUID();
		const auto transform = transforms->GetTransform(imageUID, referenceImage);
		if (transform->IsValid() && imageUID != referenceImage)
		{
			auto vtkTrans = misMathUtils::CreateVtkTransform(transform->GetTransform());
			auto tgtMat = misMathUtils::CreateTgtMatrix4d(vtkTrans->GetMatrix());
			const auto handleName = handle->getVolume()->getTexture()->getName();
			SetTranformMatrixToVolumes(handleName, tgtMat);
			ModifyVolume();
		}
	}
}

