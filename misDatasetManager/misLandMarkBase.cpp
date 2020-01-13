#include "StdAfx.h"
#include "misLandMarkBase.h"

#include "misDataSetsUtility.h"
#include "misStringTools.h"

 
misLandMarkBase::misLandMarkBase(void)
{
	m_UIDSetOccurance = -1;
    m_DataObjectUID   = misStringTools::GenerateNewUID();
}

misLandMarkBase::~misLandMarkBase(void)
{
}

misResultCode::ResultIds misLandMarkBase::insertNextPoint( misLandmarkPointStrct newPoint )
{
   misResultCode::ResultIds result = misResultCode::ErXXXUnknownError;

  try
  {
     this->m_Points.push_back(newPoint);
	 result = misResultCode::NoError;
  }
  catch (std::exception* e)
  {
  	 result = misResultCode::ErUnableToAddIntheList;
	 cout<<e->what();
  }
  
  return  result; 
}

misLandmarkPointStrct* misLandMarkBase::GetPoint( int id )
{

	int listSize = this->m_Points.size();

	if ( (id < 0) || (id >= listSize))
	{
		return 0;
	}
	
	misLandmarkPointStrct*  pPoint = new misLandmarkPointStrct;	
	misLandmarkListTypdef::iterator  listIterator;
    
	listIterator = this->m_Points.begin();
	for(int i=0; i< id; i++)
	{
      listIterator++;
	}
	// TODO: check
	misLandmarkPointStrct point = *listIterator;
	pPoint->position = point.position;
	pPoint->direction = point.direction;


	return pPoint;
}

misResultCode::ResultIds misLandMarkBase::DeletePoint( int id )
{
	 misResultCode::ResultIds result;
	
	int listSize = this->m_Points.size();

	if ( (id < 0) || (id >= listSize))
	{
		result  = misResultCode::ErInValidIdInTheList;
		return result;
	}


	misLandmarkListTypdef::iterator  listIterator;

	listIterator = this->m_Points.begin();
	for(int i=0; i< id; i++)
	{
		listIterator++;
	}

	this->m_Points.erase(listIterator);
    result  = misResultCode::NoError;
	return result;

}

misResultCode::ResultIds misLandMarkBase::DeletePoint( misLandmarkPointStrct point )
{
	int positionID;
	misResultCode::ResultIds result;
    positionID = this->FindClosestPointID(point);

	if (-1 == positionID)
	{
		result = misResultCode::ErUnableToFindInList;
		return result;
	}
    result = this->DeletePoint(positionID);

	return result;
}

misResultCode::ResultIds misLandMarkBase::DeleteAllPoints( void )
{
   misResultCode::ResultIds result;
   this->m_Points.clear();

   result  = misResultCode::NoError;
   return result;
}





misLandmarkPointStrct* misLandMarkBase::FindClosestPoint(misLandmarkPointStrct point)
{
	int pointID;
	pointID = this->FindClosestPointID(point);
    
	if (-1 == pointID)
		return 0;

    misLandmarkPointStrct* pointInList;	
    pointInList = this->GetPoint(pointID);
    
	return pointInList;
}

int   misLandMarkBase::FindClosestPointID(misLandmarkPointStrct point)
{
   
	int listSize = this->m_Points.size();

	if ( 0 == listSize)
	{
        return -1;
	}

    int selectedPosition = 0;

	misLandmarkPointStrct pointInList;	
	misLandmarkListTypdef::iterator  listIterator;

	double minDistance, distance;
    listIterator = this->m_Points.begin();
    pointInList = *listIterator;
	minDistance = misLandmarkPointStrct::EuclideanDistance(point,pointInList);
	
   int counter = -1;
	for(listIterator = this->m_Points.begin(); listIterator != this->m_Points.end(); listIterator++)
	{    
		counter ++;
		pointInList = *listIterator;      
		distance = misLandmarkPointStrct::EuclideanDistance(point,pointInList);
		if (distance <= minDistance)
		{
	       minDistance = distance;
           selectedPosition = counter;
		}

	}
	return selectedPosition;
}

double   misLandMarkBase::FindClosestPointDistanceTo(misLandmarkPointStrct point)
{

	int selectedPosition = 0;

	misLandmarkPointStrct pointInList;	
	misLandmarkListTypdef::iterator  listIterator;

	double minDistance, distance;
	listIterator = this->m_Points.begin();
	pointInList = *listIterator;
	minDistance = misLandmarkPointStrct::EuclideanDistance(point,pointInList);

	int counter = -1;
	for(listIterator = this->m_Points.begin(); listIterator != this->m_Points.end(); listIterator++)
	{    
		counter ++;
		pointInList = *listIterator;      
		distance = misLandmarkPointStrct::EuclideanDistance(point,pointInList);
		if (distance <= minDistance)
		{
			minDistance = distance;
			selectedPosition = counter;
		}

	}
	return minDistance;
}


int misLandMarkBase::FindExactPointID( misLandmarkPointStrct point )
{

	
	misLandmarkPointStrct pointInList;	
	misLandmarkListTypdef::iterator  listIterator;

	listIterator = this->m_Points.begin();

	int position = -1;
	for(listIterator = this->m_Points.begin(); listIterator != this->m_Points.end(); listIterator++)
	{   
		position++;

		pointInList = *listIterator;
		
		if (pointInList.position == point.position)
		{
           return position; 
		}

	}
  return -1;
}

void misLandMarkBase::DeepCopy( misLandMarkBase* newLandMark )
{
   if (!newLandMark)
	   return;

   this->m_ParrentUID        = newLandMark->GetParrentUID();
   this->m_ParrentObjectType = newLandMark->GetParrentObjectType();
   this->m_Points            = newLandMark->GetPoints();
}

misLandmarkListTypdef misLandMarkBase::GetPoints( void )
{
  return this->m_Points;
}

misResultCode::ResultIds misLandMarkBase::SwapPoints( int id1, int id2 )
{
	
	misResultCode::ResultIds  result;

	int listSize = this->m_Points.size();

	if ( (id1 < 0) || (id1 >= listSize))
	{
		return misResultCode::ErUnableToFindInList;
	}

	if ( (id2 < 0) || (id2 >= listSize))
	{
		return misResultCode::ErUnableToFindInList;
	}

	misLandmarkListTypdef::iterator  listIterator1;

	listIterator1 = this->m_Points.begin();
	for(int i=0; i< id1; i++)
	{
		listIterator1++;
	}

	misLandmarkListTypdef::iterator  listIterator2;

	listIterator2 = this->m_Points.begin();
	for(int i=0; i< id2; i++)
	{
		listIterator2++;
	}

    misLandmarkPointStrct point;
	point.direction = listIterator1->direction ;
	point.position  = listIterator1->position ;

	listIterator1->direction = listIterator2->direction ;
	listIterator1->position  = listIterator2->position ;

	listIterator2->direction = point.direction ;
	listIterator2->position  = point.position ;

	result = misResultCode::NoError;
	return  result;

}

misResultCode::ResultIds misLandMarkBase::UpPointInTheList( int id )
{ 
	misResultCode::ResultIds  result;
    
    result = this->SwapPoints(id , id-1);
	return   result;
}

misResultCode::ResultIds misLandMarkBase::DownPointInTheList( int id )
{
	misResultCode::ResultIds  result;

	result = this->SwapPoints(id , id+1);
	return   result;
}

int misLandMarkBase::GetNumberOfPoints( void )
{
  int size;
  size = this->m_Points.size();

  return size;
}

void misLandMarkBase::SetPoints( misLandmarkListTypdef pointList )
{
	m_Points=pointList;
}


