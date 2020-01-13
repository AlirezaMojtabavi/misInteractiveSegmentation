#include "stdafx.h"
#include "..\Header\misVoreenVolumeRenderingViewer.h"
#include "misOpenglTexture.h"
#include "misSelectionElement.h"
#include "misVoreenRepresentation.h"
#include "misVolumePointPicker.h"


misVoreenVolumeRenderingViewer::misVoreenVolumeRenderingViewer(vtkSmartPointer<vtkRenderer> renderer)
	:m_Renderer(renderer)
{
}


void misVoreenVolumeRenderingViewer::PassVolumeMapToRepresentation()
{
 	m_VoreenRepresentation->SetRenderer(m_Renderer);
    const auto rendererSize = m_Renderer->GetSize();
    const tgt::ivec3 size(rendererSize[0], rendererSize[1], 1);
	const tgt::ivec3 minimumWWindowSize(64, 64, 1);
	if(rendererSize[0] * rendererSize[1] <= 64*64)
		m_VoreenRepresentation->SetWindowSize(minimumWWindowSize);
	else
		m_VoreenRepresentation->SetWindowSize(size);
	m_VoreenRepresentation->ClearTextureHnadleMapBeforSetVolume();
	m_VoreenRepresentation->ResetMapInShader();
	for (const auto volume  : m_VolumeMap)
	{
		m_VoreenRepresentation->SetVolume(volume.first, volume.second);
	}
	UpdateRaycastingTexture( );
}

void misVoreenVolumeRenderingViewer::UpdateWindowSize(misStrctWindowSize &size)
{
	if (!m_VoreenRepresentation)
		return;
	m_VoreenRepresentation->SetWindowSize(tgt::ivec3(size.width, size.height, 1));
}



void misVoreenVolumeRenderingViewer::SetROI(misROI data)
{
	m_VoreenRepresentation->SetROI(data.getData());
}

void misVoreenVolumeRenderingViewer::UpdateRaycastingTexture()
{
	if (!m_VoreenRepresentation)
		return;
	misVoreenActor* pActorr = dynamic_cast<misVoreenActor*> (m_VoreenRepresentation->GetActor(0));;
	if (!pActorr)
		return;

	misVoreenCanvasMapper* pMapper = dynamic_cast<misVoreenCanvasMapper*>(pActorr->GetMapper());
	if (!pMapper)
		return;

	std::vector<misSelectionElement>  selctionProp;

	if (!m_TransferFunctionSelect)
		m_TransferFunctionSelect = new misTransferFunctionSelecting();
	std::for_each(m_VolumeMap.begin(), m_VolumeMap.end(), [&](std::pair<misOpenglTexture*, ImageContainedTransferFuncs3D > element)

	{
		misSelectionElement  selction;
		selction.m_Texture = element.first;
		auto uid = element.first->getName();
		selctionProp.push_back(selction);
		m_TransferFunctionSelect->UpdateTExtureTransferFunctions(element.first, element.second);
	});
	pMapper->SetTransferFunctionSelector(m_TransferFunctionSelect);
}

void misVoreenVolumeRenderingViewer::UpdatePointPicker(vtkPicker* picker)
{
	if (!m_VoreenRepresentation)
		return;

	misVoreenActor* pActorr = dynamic_cast<misVoreenActor*> (m_VoreenRepresentation->GetActor(0));;
	if (!pActorr)
		return;

	misVoreenCanvasMapper* pMapper = dynamic_cast<misVoreenCanvasMapper*>(pActorr->GetMapper());
	if (!pMapper)
		return;
	if (picker)
	{
		auto pickerVoreen = dynamic_cast<misVolumePointPicker*>(picker);
		pickerVoreen->SetVolumeMapper(pMapper);
	}
		
}

void misVoreenVolumeRenderingViewer::SetToolPosition(double xCoord, double yCoord, double zCoord)
{
	if (m_VoreenRepresentation)
		m_VoreenRepresentation->SetToolPosition(xCoord, yCoord, zCoord);
}

void misVoreenVolumeRenderingViewer::ClippingOn()
{
	if (m_VoreenRepresentation)
		m_VoreenRepresentation->ClipingOn();
}

void misVoreenVolumeRenderingViewer::ClippingOff()
{
	m_VoreenRepresentation->ClipingOF();
}

void misVoreenVolumeRenderingViewer::SetClippingPlane(tgt::vec4 plane)
{
	if (m_VoreenRepresentation)
		m_VoreenRepresentation->SetClipingPlane(plane);
}

void misVoreenVolumeRenderingViewer::Render()
{
	auto size = m_Renderer->GetRenderWindow()->GetSize();
	if (m_VoreenRepresentation)
	{
		m_VoreenRepresentation->SetWindowSize(tgt::ivec3(size[0], size[1], 1));
		m_VoreenRepresentation->ModifyVolume();
	}

}

void misVoreenVolumeRenderingViewer::SetVolume(misOpenglTexture* pTexture, std::shared_ptr<TransFuncIntensity> transferFunction)
{
	_ASSERT(0 != pTexture);
	_ASSERT(0 != transferFunction);
	if (pTexture == 0 || transferFunction == 0)
	{
		return;
	}
	RemoveVolumeWithId(pTexture->GetImageUID());

	SegmentedObjectTransferFunction3D mainImageTF;
	mainImageTF.transferFunction = transferFunction;
	ImageContainedTransferFuncs3D mainImageTransferFunctionsVec;
	mainImageTransferFunctionsVec.push_back(mainImageTF);
	m_VolumeMap[pTexture] = mainImageTransferFunctionsVec;

	PassVolumeMapToRepresentation();
}

void misVoreenVolumeRenderingViewer::SetVolume(misOpenglTexture* imageTexture, ImageContainedTransferFuncs3D ImgCntTfs)
{
	RemoveVolumeWithId(imageTexture->GetImageUID());
	m_VolumeMap[imageTexture] = ImgCntTfs;
	PassVolumeMapToRepresentation();
}

void misVoreenVolumeRenderingViewer::ModifyVolume()
{
	if (m_VoreenRepresentation)
		m_VoreenRepresentation->ModifyVolume();
}

void misVoreenVolumeRenderingViewer::CompileVolumeShader()
{
	if (m_VoreenRepresentation)
		m_VoreenRepresentation->CompileVolumeShader();
}
 

void misVoreenVolumeRenderingViewer::RemoveVolumeWithId(misUID ID)
{
	for (auto itr = m_VolumeMap.begin(), ite = m_VolumeMap.end(); itr != ite;)
	{
		if (itr->first->GetImageUID() == ID)
		{
			itr = m_VolumeMap.erase(itr);
		}
		else
			++itr;
	}
}
void misVoreenVolumeRenderingViewer::RemoveSegmentedVolume()
{
	//NOET: remove only segmented object volume based on allocatedByte size
	//just in segmented object allocatedByte size is greater than 0	// 
	if (m_VolumeMap.empty())
		return;
	for (auto mapIter = m_VolumeMap.begin(); mapIter != m_VolumeMap.end(); )
	{
		bool erased = false;
		for (int i = 0; i < mapIter->second.size(); i++)
		{
			if (mapIter->second[i].allocatedByte.size() > 0)
			{
				mapIter = m_VolumeMap.erase(mapIter);
				erased = true;
				break;
			}
		}
		if (!erased)
			mapIter++;
	}
	PassVolumeMapToRepresentation();
}

void misVoreenVolumeRenderingViewer::RemoveOldTexture(misOpenglTexture* oldTexture)
{
	if (oldTexture == 0)
	{
		_ASSERT(0 == 1);
		return;
	}

	if (m_VolumeMap.empty())
	{
		return;
	}

	if (m_VolumeMap.find(oldTexture) != m_VolumeMap.end())
	{
		m_VolumeMap.erase(oldTexture);
	}
}

void misVoreenVolumeRenderingViewer::RemoveRenderingVolume()
{
	std::map<misOpenglTexture*, ImageContainedTransferFuncs3D>::iterator mapIter;
	for (mapIter = m_VolumeMap.begin(); mapIter != m_VolumeMap.end(); mapIter++)
	{
		if (mapIter->second.size() == 1)
		{
			if (mapIter->second[0].allocatedByte.size() == 0)
			{
				m_VolumeMap.erase(mapIter->first);
				break;
			}
		}
	}
}

std::map<misOpenglTexture *, ImageContainedTransferFuncs3D> misVoreenVolumeRenderingViewer::GetVolumeMap() const
{
	return m_VolumeMap;
}


void misVoreenVolumeRenderingViewer::SetRenderer(vtkSmartPointer<vtkRenderer> val)
{
	m_Renderer = val;

}

void misVoreenVolumeRenderingViewer::Reset()
{
	if (!m_VoreenRepresentation)
		return;
	m_VolumeMap.clear();
	PassVolumeMapToRepresentation();
}

std::shared_ptr<IvolumeRepresentation> misVoreenVolumeRenderingViewer::GetRepresentation() const
{
	return m_VoreenRepresentation;
}

void misVoreenVolumeRenderingViewer::SetRepresentation(std::shared_ptr<IvolumeRepresentation> volumeRep)
{
	m_VoreenRepresentation = volumeRep;
}

