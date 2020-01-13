#include "stdafx.h"
#include "misDefaultVolumeRenderer.h"
#include "misVolumeRenderingStrategy.h"
#include "misDatasetManager.h"
#include "misImageToTextureMap.h"
#include "misMathUtils.h"
#include "IvolumeRepresentation.h"
#include "VolumeViewerInitilizer.h"
#include "misRepresentationFactory.h"


misDefaultVolumeRenderer::misDefaultVolumeRenderer(
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
	std::shared_ptr<IVolume3DRenderer> viewer, std::shared_ptr<IVolumeViewerInitilizer> volumeInitializer)
	: m_CSCorrelationManager(correlationManger),
	  m_viewer(viewer),
m_VolumeInitilizer(volumeInitializer)

{
}

 

void misDefaultVolumeRenderer::ShowDefaultVolume(int SegmentedNum, ImageDependencyListTypes currentImageDataDependencies,
	misVolumeViewingTypes volumeViewing)
{
	if (!m_CSCorrelationManager || currentImageDataDependencies.empty())
	{
		return;
	}
	auto 	defaultVolumeRnderingStrategy = std::make_unique<misVolumeRenderingStrategy>(currentImageDataDependencies,
		m_CSCorrelationManager, volumeViewing, SegmentedNum);
	auto selectedImage = defaultVolumeRnderingStrategy->GetSelctedImage();
	auto repfactory = std::make_shared<misRepresentationFactory>();
	m_VolumeInitilizer->SetWidgetType(m_WidgetType);
	m_VolumeInitilizer->Initialize(selectedImage);
	auto transfunc = defaultVolumeRnderingStrategy->getTransferFunction(selectedImage);
	misImageToTextureMap*  TextureHandler = misImageToTextureMap::GetInstance();
	misOpenglTexture* tex = TextureHandler->LookUpTexture(selectedImage);
	m_viewer->SetVolume(tex, transfunc);
	vtkSmartPointer<vtkMatrix4x4> volMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
	auto transform = m_CSCorrelationManager->GetTransform(selectedImage->GetUID(), m_SceneReferenceUID);
	if (transform->IsValid())
	{
		double elements[16];
		transform->GetTransform()->GetMarixElements(elements);
		volMatrix = misMathUtils::CreateMatrixFromMatrixElemnts(elements);
	}
	tgt::mat4 transformMatrix = tgt::mat4::Matrix4(
		volMatrix->GetElement(0, 0), volMatrix->GetElement(0, 1), volMatrix->GetElement(0, 2), volMatrix->GetElement(0, 3),
		volMatrix->GetElement(1, 0), volMatrix->GetElement(1, 1), volMatrix->GetElement(1, 2), volMatrix->GetElement(1, 3),
		volMatrix->GetElement(2, 0), volMatrix->GetElement(2, 1), volMatrix->GetElement(2, 2), volMatrix->GetElement(2, 3),
		0, 0, 0, 1);
	SetTranformMatrixToVolumes(selectedImage->GetUID(), transformMatrix);
}

void misDefaultVolumeRenderer::SetTranformMatrixToVolumes(const std::string& id, const tgt::mat4& matrix)
{
	auto volumeRep = std::dynamic_pointer_cast<IvolumeRepresentation>(m_viewer->GetMainRepresentation());
	if (!volumeRep)
	{
		return;
	}
	volumeRep->SetTranformMatrixToVolumes(id, matrix);
}
void misDefaultVolumeRenderer::SetWidgetType(misCursorType pWidgetType)
{
	m_WidgetType = pWidgetType;
}

void misDefaultVolumeRenderer::SetSceneReferenceUID(const std::string & sceneReferenceUID)
{
	m_SceneReferenceUID = sceneReferenceUID;
}
