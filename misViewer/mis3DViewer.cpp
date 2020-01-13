#include "stdafx.h"
#include "mis3DViewer.h"

#include "misAnnotationRepresentation.h"
#include "misMathUtils.h"
#include "IPartialVolumeBaseRepresentation.h"
#include "misException.h"
#include "misFollowerFixedArea.h"
 
using namespace std;


mis3DViewer::mis3DViewer(vtkPicker* picker)
	:m_IndexInGroup(0), m_ShowFPS(false), m_Active(true) , m_3dStyle (NULL),
	m_ScaleCameraPosition(3), m_GlExtensionLoaded(false), m_Timer(vtkTimerLog::New()),m_AverageRenderTime(0), m_RenderCount (0),
	m_Picker(picker)
{
	std::fill(m_BoundingBox, m_BoundingBox + 6 , 0);
	std::fill(m_FocalPoint, m_FocalPoint + 3 , 0);
}

void mis3DViewer::WindowSizeChanged(itk::Object *caller, const itk::EventObject & event)
{
	const  misWindwsSizeChangedEvent* pEvent = dynamic_cast<const misWindwsSizeChangedEvent*>(&event);
	if (pEvent)
	{
		misStrctWindowSize  size = pEvent->Get();

		UpdateWindowSize(size);

	}

}

mis3DViewer::~mis3DViewer()
{
	Reset();
}

void mis3DViewer::Reset()
{	
	// Add representations that should be removed 
 	std::for_each(m_Representations.begin(), m_Representations.end(), [&] (auto rep)
	{
 		RemoveRepresentation(rep);
	});

	// Remove all the spatial objects in an iterator safe manner
	std::list<misSpatialObject::Pointer> spatialObjectsToRemove(m_SpatialObjects.begin(), m_SpatialObjects.end());
	std::for_each(spatialObjectsToRemove.begin(), spatialObjectsToRemove.end(), [&] (misSpatialObject::Pointer rep)
	{
		RemoveSpatialObject(rep);
	});

	if(m_Renderer)
		m_Renderer->RemoveAllViewProps();
	m_Representations.clear();
	m_FocalPoint[0] = m_FocalPoint[1] = m_FocalPoint[2] = 0;
}


void mis3DViewer::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	if(!pRepresent || m_Representations.empty())
		return;
 	auto foundRepresent = std::find(m_Representations.begin(), m_Representations.end(), pRepresent);
	if (foundRepresent != m_Representations.end())
	{		
		for(auto prop: pRepresent->GetActors())
			m_Renderer->RemoveViewProp(prop);
		m_Representations.erase(foundRepresent);
	}
}

void mis3DViewer::RemoveSpatialObject( misSpatialObject::Pointer spatialObject )
{
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

void mis3DViewer::AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation)
{
	if (!CheckNewRepresentationValidity(pRepresentation))
		return;
	auto actors = pRepresentation->GetActors();
	if(actors.empty())
		return;
	m_Representations.push_back(pRepresentation);
 	for (auto actor : actors)
	{
		auto  pFollow = dynamic_cast<misFollowerFixedArea*>(actor.GetPointer());
		if (pFollow)
			pFollow->SetCamera(m_Renderer->GetActiveCamera());
		m_Renderer->AddViewProp(actor);
 	}
	UpdateBoundingBox();
} 

void mis3DViewer::AddSpatialObject( misSpatialObject::Pointer spatialObject )
{
	if (!CheckNewSpatialObjectValidity(spatialObject))
		throw misException("Invalid attempt to add spatial object: either null or duplicate object.");

	
	m_SpatialObjects.push_back(spatialObject);

	for (auto propItr = spatialObject->GetProps().begin(); propItr != spatialObject->GetProps().end(); propItr++)
	{
		misFollowerFixedArea* pFollow = dynamic_cast<misFollowerFixedArea*>((*propItr).GetPointer());
		if (pFollow)
			pFollow->SetCamera(m_Renderer->GetActiveCamera());

		m_Renderer->AddViewProp(*propItr);
	}
	UpdateBoundingBox();
}

void mis3DViewer::UpdateBoundingBox(void)
{
	double bounds[6] = { 0,0,0,0,0,0 };
	std::fill(m_BoundingBox, m_BoundingBox + 6, 0);

	for( auto reprerntation : m_Representations)
	{
		if ((reprerntation->GetObjectName() != "Man Model") && 
			(reprerntation->GetObjectName() != "Tool" ) &&
			(reprerntation->GetObjectName() != "misLandmarkPointerRepresentation"))
		{
			bool merge = reprerntation->GetBoundingBox(bounds);
			if (merge)
				misMathUtils::MergeBounding(m_BoundingBox,bounds,m_BoundingBox);
		}
	}
	for_each(m_SpatialObjects.begin(), m_SpatialObjects.end(), [&] (misSpatialObject::Pointer spObj)
	{
		bool merge = spObj->GetBoundingBox(bounds);
		if (merge)
			misMathUtils::MergeBounding(m_BoundingBox, bounds, m_BoundingBox);
	});
	if (m_BoundingBox[1] - m_BoundingBox[0]  == 0)
	{
		m_BoundingBox[0] = 0;
		m_BoundingBox[1] = 300;
	}
	if (m_BoundingBox[3] - m_BoundingBox[2] == 0)
	{
		m_BoundingBox[2] = 0;
		m_BoundingBox[3] = 300;
	}
	if (m_BoundingBox[5] - m_BoundingBox[4] == 0)
	{
		m_BoundingBox[4] = 0;
		m_BoundingBox[5] = 300;
	}
}

void mis3DViewer::GetWindowSize(int* size) const
{
	auto window = GetWindow();
	if (!window)
		return;
	auto renderWindow = window->GetRenderWindow();
	if (!renderWindow)
		return;
	HWND  windowHandle = (HWND)renderWindow->GetGenericWindowId();

	RECT  rc;
	GetClientRect(windowHandle, &rc);
	size[0] = rc.right - rc.left;
	size[1] = rc.bottom - rc.top;
}

 

RepresentionsListType mis3DViewer::GetRepresentations() const
{
	return m_Representations;
}

MIS3DInteractionStyle* mis3DViewer::Get3DStyle() const
{
	return m_3dStyle;
}

bool mis3DViewer::IsWindowsSizeChanged() const
{
	int size[2];
	GetWindowSize(size);
	bool windowSizeChanged = (m_WindowSizeUpdated[0] != size[0]) || (m_WindowSizeUpdated[1] != size[1]);
	return windowSizeChanged;
}

void mis3DViewer::Render()
{
	auto windowSize =  m_Window->GetWindowSize();
	auto windowsArea = windowSize.width* windowSize.width;
	if (windowsArea < 100)
		return;
	if (!m_Renderer)
		return;
	try
	{
		m_Timer->StartTimer();
		UpdateCoordinateTransforms();
		if (m_Active)
			m_Renderer->GetRenderWindow()->Render();
		m_Timer->StopTimer();
		double elpsedTime = m_Timer->GetElapsedTime() * 1000; // in milliseconds
		UpdateAverageRenderTime(elpsedTime);
	}
	catch (const std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Exception thrown in the rendering pipeline - misVolumeSlicer::Render(). Exception message: " <<
			e.what() << std::endl;
		std::cout << errorMessage.str();

	}
	catch(...)
	{
		std::string errorMessage("Exception of unknown type thrown in the rendering pipeline - mis3DViewer::Render().");
		std::cout << errorMessage;
 
	}
	LogOpenGLError();
}

void mis3DViewer::UpdateCoordinateTransforms()
{
	std::for_each(m_CoordinateRenderers.begin(), m_CoordinateRenderers.end(),
		[&](std::shared_ptr<ICoordinateSystemRenderer> coordinateRenderer)
	{
		coordinateRenderer->Render();
	});
}

void mis3DViewer::LogOpenGLError()
{
	auto openGLError = glGetError();
	if (openGLError != GL_NO_ERROR)
	{
		std::ostringstream errorMessage;
		errorMessage << "OpenGL error in the rendering pipeline - mis3DViewer::Render() -> Error Code: " << 
			openGLError << std::endl;
		std::cout << errorMessage.str();
 
	}
}

void  mis3DViewer::ResetCamera()
{
	m_Renderer->ResetCamera();
}

void mis3DViewer::AddAxis(misAxisProperty  axis)
{
	vtkAxesActor* pAxes=vtkAxesActor::New();
	if (axis.GetGeoType() == misAxisProperty::cylinder)
		pAxes->SetShaftTypeToCylinder();
	else
		pAxes->SetShaftTypeToLine();
	
	pAxes->SetXAxisLabelText( "X" );
	pAxes->SetYAxisLabelText( "Y" );
	pAxes->SetZAxisLabelText( "Z" );
	pAxes->SetTotalLength( axis.GetXLenght(), axis.GetYLenght(), axis.GetZLenght());
	m_Renderer->AddActor(pAxes);
	pAxes->Delete();
}

void mis3DViewer::AddAxis( double x, double y ,double z )
{
	vtkAxesActor* pAxes=vtkAxesActor::New();
	pAxes->SetShaftTypeToCylinder();
	pAxes->SetXAxisLabelText( "X" );
	pAxes->SetYAxisLabelText( "Y" );
	pAxes->SetZAxisLabelText( "Z" );
	pAxes->SetTotalLength( x,y,z);
	m_Renderer->AddActor(pAxes);
	pAxes->Delete();
}

void mis3DViewer::SetWindow(std::shared_ptr<Iwindows> pWindow,  int index)
{
	m_IndexInGroup = index;
	m_Renderer = pWindow->GetRenderer(index);
	auto cullers = m_Renderer->GetCullers();
	vtkCollectionSimpleIterator sit;
	vtkCuller *aCuller;
	for (cullers->InitTraversal(sit);
		(aCuller = cullers->GetNextCuller(sit));)
	{
		m_Renderer->RemoveCuller(aCuller);
	}

	m_Renderer->GetActiveCamera()->SetClippingRange(1, 5000);
	m_Window = pWindow;
	if (!Get3DStyle())
		Set3DStyle(MIS3DInteractionStyle::New(m_Picker));
	vtkRenderWindowInteractor*  pInteractor = m_Window->GetRenderer(index)->GetRenderWindow()->GetInteractor();
	if (pInteractor)
		if (!Get3DStyle()->HasObserver(interctionEvent))
			m_Window->GetRenderer(index)->GetRenderWindow()->GetInteractor()->SetInteractorStyle(Get3DStyle());

	if (!m_GlExtensionLoaded)
	{
		glewInit();
		m_GlExtensionLoaded = true;
	}
}

void mis3DViewer::AddAnnotation( char* Text,tgt::vec2   position)
{
	if (m_Renderer)
	{
		auto windowSize = m_Renderer->GetRenderWindow()->GetSize();
		std::string emptyString;
		std::shared_ptr<misAnnotationRepresentation> annottaion = std::make_shared<misAnnotationRepresentation>("");
		annottaion->SetText(Text);
		annottaion->WindowSize(tgt::vec2(static_cast<float> (windowSize[0]), static_cast<float>  (windowSize[1])));
		annottaion->SetPosition(position[0],position[1]);
		AddRepresentation(annottaion);
 	}
}

MIS3DInteractionStyle * mis3DViewer::Get3dStyleCamera()
{
	return Get3DStyle();
}

vtkRenderer* mis3DViewer::GetRenderer()
{
	return m_Renderer;
}

void mis3DViewer::SetCroppingDirection(misCroppingDirectionInVR croppingDirection)
{
	std::for_each(m_Representations.begin(), m_Representations.end(), [&croppingDirection] (auto rep)
	{
		auto pVolumeRep = std::dynamic_pointer_cast<IPartialVolumeBaseRepresentation> (rep);
		if (pVolumeRep)
			pVolumeRep->SetCroppingDirection(croppingDirection);
	} );
}

RepresentionsListType mis3DViewer::GetRepresentation()
{
	return m_Representations;
}

int mis3DViewer::GetNumberOfRepresentations( void )
{
	auto repNumber = m_Representations.size();
	return static_cast<int >(repNumber);
}

bool mis3DViewer::GetViewerActivity() const
{
	return m_Active;
}

void mis3DViewer::SetViewerActivity( bool val )
{
	m_Active = val;
}

bool mis3DViewer::CheckNewRepresentationValidity(std::shared_ptr<IRepresentation> pRepresentation )
{
	bool res = true;
	if (0 == pRepresentation)
	{
		res = false;
	}
	else
	{
 		auto representationItr = std::find(m_Representations.cbegin(), m_Representations.cend(), pRepresentation);
		if (representationItr != m_Representations.end())
		{
			res = false;
		}
	}
	return res;
}

void mis3DViewer::SetWindowSizeUpdated(int val0, int val1)
{
	misStrctWindowSize size;
	size.width = val0;
	size.height = val1;
	UpdateWindowSize(size);

}

const double* mis3DViewer::GetFocalPoint() const
{
	return m_FocalPoint;
}

void mis3DViewer::SetFocalPoint(double val0, double val1, double val2)
{
	m_FocalPoint[0] = val0;
	m_FocalPoint[1] = val1; m_FocalPoint[2] = val2;
}

int mis3DViewer::GetIndexInGroup() const
{
	return m_IndexInGroup;
}

std::vector<std::shared_ptr<ICoordinateSystemRenderer>> mis3DViewer::GetCoordinateRenderers() const
{
	return m_CoordinateRenderers;
}

const double* mis3DViewer::GetBoundingBox() const
{
	return m_BoundingBox;
}

 

double mis3DViewer::GetScaleCameraPosition() const
{
	return m_ScaleCameraPosition;
}

void mis3DViewer::SetScaleCameraPosition(double val)
{
	m_ScaleCameraPosition = val;
}

MIS3DInteractionStyle* mis3DViewer::GetM_3dStyle() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void mis3DViewer::SetM_3dStyle(MIS3DInteractionStyle* val)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void mis3DViewer::SetBoundingBox(double* val)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool mis3DViewer::CheckNewSpatialObjectValidity( misSpatialObject::Pointer spatialObject )
{
	if (!spatialObject)
		return false;
	
	// Check for duplicates
	misSpatialObjectListType::iterator findResult = std::find(m_SpatialObjects.begin(), m_SpatialObjects.end(), spatialObject);
	if (findResult != m_SpatialObjects.end())
		return false;

	// All good!
	return true;
}


std::shared_ptr<Iwindows>  mis3DViewer::GetWindow() const
{
	return m_Window;
}

void mis3DViewer::UpdateRepresentationActors()
{
	if (m_Renderer->GetActors())
	{
		vtkActorCollection* allActorsAdded = m_Renderer->GetActors();
		std::list<vtkProp*> newActors;
		std::list<vtkProp*> allActor;
		RepresentionsListType::iterator  itrBegin= m_Representations.begin();
		RepresentionsListType::iterator  itrEnd= m_Representations.end();
		
		for_each(itrBegin, itrEnd, [&](std::shared_ptr<IRepresentation>  &p)
		{
			auto oldActors = p->GetActors();
			allActor.insert(allActor.begin(), oldActors.begin(), oldActors.end());
		});

		for_each(allActor.begin(),allActor.end(),[&](vtkProp* prop)
		{
			vtkProp* addedProp=0;
			bool  exist=false;
			while ( addedProp=allActorsAdded->GetNextActor())
			{
				if (addedProp==prop)
				{
					exist=true;
					break;
				}
			}
			if(!exist)
				newActors.push_back(prop);
		});

		for_each(newActors.begin(), newActors.end(), [&](vtkProp* prop)
		{
			m_Renderer->AddViewProp(prop);
		});
	}
	
}

void mis3DViewer::UpdateFocalPoint( void )
{
	UpdateBoundingBox();
	m_FocalPoint[0]=(m_BoundingBox[1]-m_BoundingBox[0])*0.5;
	m_FocalPoint[1]=(m_BoundingBox[3]-m_BoundingBox[2])*0.5;
	m_FocalPoint[2]=(m_BoundingBox[5]-m_BoundingBox[4])*0.5;
}

void mis3DViewer::SetDefaultFocalPoint( void )
{
	UpdateFocalPoint();
	m_Renderer->GetActiveCamera()->SetFocalPoint(m_FocalPoint[0],m_FocalPoint[1],m_FocalPoint[2]);
}

void mis3DViewer::GetDefaultFocalPoint( double focalPoint[3] )
{
	UpdateFocalPoint();

	focalPoint[0] = m_FocalPoint[0];
	focalPoint[1] = m_FocalPoint[1];
	focalPoint[2] = m_FocalPoint[2];
}



void mis3DViewer::AddFPSRenderer()
{
	if(!m_pFpsReprsentation)
		m_pFpsReprsentation = std::make_shared<misTextRepresentation>("");
	auto itr = find(m_Representations.begin(), m_Representations.end(), m_pFpsReprsentation);
	if (itr == m_Representations.end())
		AddRepresentation(m_pFpsReprsentation);
}

void mis3DViewer::ShowFPSOn()
{
	m_ShowFPS = true;
	AddFPSRenderer();
}

void mis3DViewer::ShowFPSOff()
{
	m_ShowFPS = false;
	if(m_pFpsReprsentation)
		RemoveRepresentation(m_pFpsReprsentation);
}

void mis3DViewer::SetFPS( double  fps )
{
	if (!m_ShowFPS)
		return;
	std::ostringstream buff;
	buff << "FPS: " << fps;
	if (m_pFpsReprsentation)
	{
		m_pFpsReprsentation->SetText(buff.str());
		m_pFpsReprsentation->SetPosition2D(60,60);
	}
}

double mis3DViewer::GetAverageRenderTime( void )
{ 
	return m_AverageRenderTime;
}

void mis3DViewer::UpdateAverageRenderTime( double elpsedTime )
{
	m_AverageRenderTime = (59 * m_AverageRenderTime + elpsedTime) / (60);
}

void mis3DViewer::RemoveRepresentationByName(std::string name )
{
	auto newEnd = std::remove_if(m_Representations.begin(),m_Representations.end(),[name, this](auto rep)->bool
	{
		if (rep->GetObjectName() == name)
		{
			vtkRenderer* pRenderer = m_Renderer;
			auto oldActors = rep->GetActors();
			std::for_each(oldActors.begin(), oldActors.end() ,[&](vtkSmartPointer<vtkProp>  prop)
			{
				if (pRenderer)
					pRenderer->RemoveViewProp(prop);
			});
			return true;
		}
		return  false;
	});
	m_Representations.resize(newEnd- m_Representations.begin());
}


void mis3DViewer::SetViewPort( const misViewPort& val )
{
	m_ViewPort = val;
	if(m_Renderer)
		m_Renderer->SetViewport(GetViewPort().GetStart().x, GetViewPort().GetStart().y, GetViewPort().GetEnd().x, GetViewPort().GetEnd().y);
}

misViewPort mis3DViewer::GetViewPort() const
{
	return m_ViewPort;
}

void mis3DViewer::AddCoordinateSytemRenderer( std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer )
{
	m_CoordinateRenderers.push_back(coordianteRenderer);
}

std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> mis3DViewer::GetCoordianteSystemCorrelationManager() const
{
	return m_CoordianteSystemCorrelationManager;
}

void mis3DViewer::SetCoordianteSystemCorrelationManager( std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> val )
{
	m_CoordianteSystemCorrelationManager = val;
}

void mis3DViewer::UpdateWindowSize(misStrctWindowSize &size)
{
	if (!m_Renderer)
		return;
	if (!IsWindowsSizeChanged())
		return;
	m_WindowSizeUpdated[0] = size.width;
	m_WindowSizeUpdated[1] = size.height;
	auto renderWindow = m_Renderer->GetRenderWindow();
	if(renderWindow)
		renderWindow->SetSize(size.width, size.height);
}

std::vector<std::shared_ptr<IRepresentation>> mis3DViewer::FindRepresentationByName(const std::string& name )
{
	std::vector<std::shared_ptr<IRepresentation>> representations;
	for(int i = 0; i < m_Representations.size(); i++)
	{
		if (m_Representations[i]->GetObjectName() == name)
			representations.push_back(m_Representations[i]);
	}
	return representations;
}

