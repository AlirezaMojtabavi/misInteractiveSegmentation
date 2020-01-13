#include "StdAfx.h"
#include "misAnnoatationGroupRep.h"

using std::for_each;
using std::string;
using std::vector;

misAnnoatationGroupRep::misAnnoatationGroupRep(std::string name):misRepresentation(name)
{
}


misAnnoatationGroupRep::~misAnnoatationGroupRep(void)
{
}
void misAnnoatationGroupRep::AddActors( vector<vtkSmartPointer<vtkTextActor>> pActorList )
{
	for_each(pActorList.begin(),pActorList.end(),[&](vtkSmartPointer<vtkTextActor>  pactor)

	{
		
		this->m_Actors.push_back(pactor);
	});

}


 