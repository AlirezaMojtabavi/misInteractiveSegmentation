#include "StdAfx.h"
#include "misSpatialObject.h"

#include "misMathUtils.h"

misSpatialObject::misSpatialObject()
	: m_IsBoundingBoxCalculated(false)
{
	for (int i = 0; i < 6; i++)
		m_BoundingBox[i] = 0;
}

misSpatialObject::~misSpatialObject()
{
}

const misSpatialObject::PropsListType &misSpatialObject::GetProps() const
{
	return m_PropsList;
}

void misSpatialObject::SetUserTransform( vtkSmartPointer<vtkTransform> transform )
{
	m_Transform = transform;
	m_IsBoundingBoxCalculated = CalculateBoundingBox(m_BoundingBox);
}

vtkSmartPointer<vtkTransform> misSpatialObject::GetUserTransform() const
{
	return m_Transform;
}

bool misSpatialObject::GetBoundingBox( double bounds[6] ) const
{
	for (int i = 0; i < 6; i++)
		bounds[i] = m_BoundingBox[i];
	return m_IsBoundingBoxCalculated;
}

void misSpatialObject::AddProp( vtkSmartPointer<vtkProp> prop )
{
	if (!prop)
		return;
	m_PropsList.push_back(prop);
	m_IsBoundingBoxCalculated = CalculateBoundingBox(m_BoundingBox);
}

bool misSpatialObject::CalculateBoundingBox( double bounds[6] )
{
	// Get the first prop on the list, use its bounds for the initial result, then iteratively union it with subsequent props on the
	// list.

	// Set the resultant bounds as the bounds of the first prop on the list that has defined bounds.
	double *resultantBounds = NULL;
	auto propItr = m_PropsList.begin();
	for (; !resultantBounds && propItr != m_PropsList.end(); propItr++)
	{
		resultantBounds = (*propItr)->GetBounds();
	}

	if (!resultantBounds)	// None of the constituent props have defined bounds or not props added. Fail.
		return false;	

	// Compute union of the computed result with each one of the props on the list iteratively.
	for (; propItr != m_PropsList.end(); propItr++)	// Iterated props so far have been accounted for.
	{		
		double * currentPropBounds = (*propItr)->GetBounds();
		if (currentPropBounds)
		{
			// Compute union of the current prop bounds and the resultant bounds computed so far, put it back in the resultant.
			misMathUtils::MergeBounding(bounds, resultantBounds, resultantBounds);
		}
	}

	// Copy the result to the output bounds parameter and return true for success.
	for (int i = 0; i < 6; i++)
		bounds[i] = resultantBounds[i];
	return true;
}

void misSpatialObject::DeleteProp( vtkSmartPointer<vtkProp> prop )
{
	if (!prop)
		return;

	std::remove_if(m_PropsList.begin(), m_PropsList.end(), [&](vtkSmartPointer<vtkProp> listProp)->bool
	{
		if (listProp == prop)
		{
			return true;
		}
		return false;
	});
	m_IsBoundingBoxCalculated = CalculateBoundingBox(m_BoundingBox);
}

void misSpatialObject::ClearProps()
{
	m_PropsList.clear();
	m_IsBoundingBoxCalculated = CalculateBoundingBox(m_BoundingBox);
}
