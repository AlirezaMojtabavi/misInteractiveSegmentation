#include "stdafx.h"
#include "misManModelrepresentation.h"

#include "misManModelActor.h"
#include "misVisualizationResourceManager.h"

using namespace std;

misManModelrepresentation::misManModelrepresentation( string name ): misSurfaceRepresentation(name)
{
}

misManModelrepresentation::~misManModelrepresentation( void )
{
}

 

void misManModelrepresentation::Init( double* pos ,vtkRenderer*  pRenderer)
{
	m_Actors.clear();
	pRenderer->GetRenderWindow()->MakeCurrent();
	misVisualizationResourceManager* pResources = misVisualizationResourceManager::GetInstance();
	auto manModel = pResources->GetManModel();
	auto pNewCollection = vtkSmartPointer<vtkActorCollection>::New();

	for_each(manModel.begin(),manModel.end(),[&](vtkActor* actor)
	{
		vtkPolyDataMapper* pPolyDataMapper=dynamic_cast<vtkPolyDataMapper*>(actor->GetMapper());	
		auto manActor = vtkSmartPointer<misManModelActor>::New();
		manActor->SetMapper(pPolyDataMapper);
		manActor->Setm_Renderer(pRenderer);
		manActor->SetCamera(pRenderer->GetActiveCamera());
		manActor->SetProperty(actor->GetProperty());
		manActor->SetObjectPosition(pos);
		pNewCollection->AddItem(manActor);
	});
	AddActors(pNewCollection);
}
