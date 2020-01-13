#include "StdAfx.h"
#include "misRenderer.h"

#include "misException.h"
#include "misMathUtils.h"

misRenderer::misRenderer(void)
{
}


misRenderer::~misRenderer(void)
{
}

void misRenderer::Initialize( RendererType rendererType )
{
	//switch (rendererType)
	//{
	//case RT_VOLUME_RENDERER:
	//	m_Renderer = vtkSmartPointer<mis3dRenderer>::New();
	//	break;
	//case RT_IMAGE_RENDERER:
	//	m_Renderer = vtkSmartPointer<misImageRenderer>::New();
	//	break;
	//case RT_DEFAULT_RENDERER:
	//	m_Renderer = vtkSmartPointer<vtkRenderer>::New();
	//	break;
	//}
	m_Renderer = vtkSmartPointer<vtkRenderer>::New();
}

void misRenderer::AddSpatialObject( misSpatialObject::Pointer spatialObject )
{
	if (!m_Renderer.GetPointer())
		throw misException("Attempt to add spatial object before initialization of misRenderer.");

	if (!CheckNewSpatialObjectValidity(spatialObject))
		throw misException("Invalid attempt to add spatial object: either null or duplicate object.");

	std::for_each(spatialObject->GetProps().cbegin(), spatialObject->GetProps().cend(), [this] (vtkSmartPointer<vtkProp> spObjProp)
	{
		m_Renderer->AddViewProp(spObjProp);
	});
	
	m_SpatialObjects.push_back(spatialObject);
	UpdateBoundingBox();
}

void misRenderer::RemoveSpatialObject( misSpatialObject::Pointer spatialObject )
{
	if (!m_Renderer.GetPointer())
		throw misException("Attempt to remove spatial object before initialization of misRenderer.");

	misSpatialObjectListType::iterator foundSpatialObjectItr = 
		std::find(m_SpatialObjects.begin(), m_SpatialObjects.end(), spatialObject);

	if (foundSpatialObjectItr != m_SpatialObjects.end())
	{
		misSpatialObject::PropsListType containedProps = (*foundSpatialObjectItr)->GetProps();
		for (auto propItr = containedProps.begin(); propItr != containedProps.end(); propItr++)
		{
			m_Renderer->RemoveViewProp(*propItr);
		}
		m_SpatialObjects.erase(foundSpatialObjectItr);
	}
}

void misRenderer::Reset()
{
	if (!m_Renderer.GetPointer())
		return;	// Nothing to do; not initialized.

	// Remove all the spatial objects in an iterator safe manner
	std::list<misSpatialObject::Pointer> spatialObjectsToRemove(m_SpatialObjects.begin(), m_SpatialObjects.end());
	std::for_each(spatialObjectsToRemove.begin(), spatialObjectsToRemove.end(), [&] (misSpatialObject::Pointer rep)
	{
		RemoveSpatialObject(rep);
	});
	m_Renderer->RemoveAllViewProps();
}

vtkRenderer* misRenderer::GetRenderer()
{
	return m_Renderer;
}

double* misRenderer::GetBounding()
{
	return m_BoundingBox;
}

bool misRenderer::CheckNewSpatialObjectValidity( misSpatialObject::Pointer spatialObject )
{
	if (!spatialObject)
		return false;

	misSpatialObjectListType::iterator findResult = std::find(m_SpatialObjects.begin(), m_SpatialObjects.end(), spatialObject);
	if (findResult != m_SpatialObjects.end())
		return false;

	return true;	// All good!
}

void misRenderer::UpdateBoundingBox( void )
{
	double bounds[6];

	for(int i = 0; i < 6; i++)
		m_BoundingBox[i] = 0;

	std::for_each(m_SpatialObjects.begin(), m_SpatialObjects.end(), [&] (misSpatialObject::Pointer spObj)
	{
		bool merge = spObj->GetBoundingBox(bounds);
		if (merge)
			misMathUtils::MergeBounding(m_BoundingBox, bounds, m_BoundingBox);
	});
}

void misRenderer::Render()
{
	if (m_Renderer.GetPointer())
		m_Renderer->Render();
}
