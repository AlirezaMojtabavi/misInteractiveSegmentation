#include "stdafx.h"
#include "misRepresentation.h"

#include "misMathUtils.h"

using std::string;

misRepresentation::misRepresentation(string name)
{
	this->m_ObjectName = name;
	this->m_Position[0] = this->m_Position[1] = this->m_Position[2] = 0;
	this->m_BoundingActorsUpdated = 0;
	this->m_BoundingBox = itk::BoundingBox<double, 3, double>::New();
}





void misRepresentation::GetPosition(double position[3])
{
	position[0] = m_Position[0];
	position[1] = m_Position[1];
	position[2] = m_Position[2];
}
//==================================================================================
void misRepresentation::SetPosition(double x, double y, double z)
{
	// TODO: check and used translate	
	this->m_Position[0] = x;
	this->m_Position[1] = y;
	this->m_Position[2] = z;

	this->CalculatedBoundingBox();

	misRepresentation::ActorsListType::iterator  it = this->m_Actors.begin();
	while (it != this->m_Actors.end())
	{
		vtkProp3D* actor = dynamic_cast<vtkProp3D*>((*it).GetPointer());
		if (actor)
			actor->SetPosition(x, y, z);

		++it;
	}


}
void misRepresentation::SetPosition(double position[3])
{

	this->CalculatedBoundingBox();

	this->m_Position[0] = position[0];
	this->m_Position[1] = position[1];
	this->m_Position[2] = position[2];
	misRepresentation::ActorsListType::iterator it = this->m_Actors.begin();
	while (it != this->m_Actors.end())
	{
		vtkProp3D* actor = dynamic_cast<vtkProp3D*>((*it).GetPointer());
		if (actor)
			actor->SetPosition(position);

		++it;
	}

}
//==============================================================================

void misRepresentation::SetUserTransform(vtkTransform *transform)
{
	this->m_pUserTramsform = transform;
	double  zeroPosition[3];
	zeroPosition[0] = zeroPosition[1] = zeroPosition[2] = 0;


	double* pos = this->m_pUserTramsform->TransformDoublePoint(zeroPosition);
	this->m_Position[0] = pos[0];
	this->m_Position[1] = pos[1];
	this->m_Position[2] = pos[2];

	for (auto prop : m_Actors)
	{
		auto  actor = dynamic_cast<vtkProp3D*>(prop.GetPointer());
		if (actor)
			actor->SetUserTransform(transform);
	}

}

vtkProp* misRepresentation::GetActor(int index)
{
	if ((m_Actors.size() > index) && (index >= 0))
	{
		return this->m_Actors[index];
	}
	else
	{
		return  NULL;
	}
}

void misRepresentation::Reset()
{
	this->m_Actors.clear();

}

bool misRepresentation::CalculatedBoundingBox()
{
	const int size = this->m_Actors.size();
	if (size == 0)
	{
		return  false;
	}
	double  bounds[6];
	double  resBound[6];
	for (auto& boxArray : this->m_BoundingBoxSimpleArray)
	{
		boxArray = 0;
	}
	const auto it = this->m_Actors.begin();
	auto* actor = dynamic_cast<vtkProp3D*>((*it).GetPointer());
	if (actor)
	{
		actor->GetBounds(resBound);
		for (auto itr = this->m_Actors.begin() + 1; itr != this->m_Actors.end(); ++itr)
		{
			auto* actor = dynamic_cast<vtkProp3D*>((*it).GetPointer());
			if (actor)
			{
				actor->GetBounds(bounds);
			}
			misMathUtils::MergeBounding(bounds, resBound, resBound);
		}
		for (auto i = 0; i < 6; i++)
		{
			this->m_BoundingBoxSimpleArray[i] = resBound[i];
		}
		m_BoundingActorsUpdated = this->m_Actors.size();
		itk::Point<double, 3>  ptmin;
		ptmin[0] = resBound[0];
		ptmin[1] = resBound[2];
		ptmin[2] = resBound[4];
		itk::Point<double, 3>  ptmax;
		ptmax[0] = resBound[1];
		ptmax[1] = resBound[3];
		ptmax[2] = resBound[5];
		this->m_BoundingBox->SetMaximum(ptmax);
		this->m_BoundingBox->SetMinimum(ptmin);
	}
	return  true;
}
//===============================================================================
itk::BoundingBox<double, 3, double>::Pointer misRepresentation::GetBoundingBox()
{
	const auto res = CalculatedBoundingBox();
	if (res)
	{
		return m_BoundingBox;
	}
	return nullptr;
}

bool misRepresentation::GetBoundingBox(double *boundingBox)
{
	const auto res = CalculatedBoundingBox();
	if (res)
	{
		for (auto i = 0; i < 6; i++)
		{
			boundingBox[i] = this->m_BoundingBoxSimpleArray[i];
		}
		return true;
	}
	return false;
}

unsigned long misRepresentation::AddObserver(const itk::EventObject & event, itk::Command *command)
{
	return m_DummyObject->AddObserver(event, command);
}

void misRepresentation::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->SetRepresenation(shared_from_this());
	m_DummyObject->InvokeEvent(event);
}

bool misRepresentation::HasObserver(const itk::EventObject & event) const
{
	return m_DummyObject->HasObserver(event);
}

misRepresentation::ActorsListType misRepresentation::GetActors() const
{
	return m_Actors;
}

void misRepresentation::SetRepresentationName(string name)
{
	this->m_ObjectName = name;
}

double* misRepresentation::GetPosition() const
{
	const auto pos = new double[3];

	pos[0] = m_Position[0];
	pos[1] = m_Position[1];
	pos[2] = m_Position[2];

	return pos;
}

void misRepresentation::AttachRepresentation(misRepresentation* prep)
{
	for (int i = 0; i < prep->m_Actors.size(); i++)
	{
		m_Actors.push_back(prep->m_Actors[i]);
	}
}

void misRepresentation::AddProp(vtkProp* prop)
{
	m_Actors.push_back(prop);

}

void misRepresentation::SetVisibility(bool value)
{
	for (int i = 0; i < this->m_Actors.size(); i++)
	{
		vtkProp* pPROP = dynamic_cast<vtkProp*>(this->m_Actors[i].GetPointer());

		if (pPROP)
			pPROP->SetVisibility(value);
	}
}

void  misRepresentation::SetVisibilityOff(void)
{
	this->SetVisibility(false);
}

void  misRepresentation::SetVisibilityOn(void)
{
	this->SetVisibility(true);
}

int misRepresentation::GetNumberOfActors()
{
	return  m_Actors.size();
}


void misRepresentation::AddActors(vtkActorCollection* pActorCollection)
{
	pActorCollection->InitTraversal();
	vtkActor* pActor = 0;
	while (pActor = pActorCollection->GetNextActor())
		this->m_Actors.push_back(pActor);
	m_BoundingActorsUpdated = this->m_Actors.size();
}

