#pragma once
#ifndef misLandMarkBase_H
#define misLandMarkBase_H
#include "misSeconderyNeededHeader.h"
#include "misDatasetMacroes.h"

class misDataSetsUtility;


class  misLandMarkBase 
{
 
public:

//Private:
	misLandmarkListTypdef   m_Points;
	
	misCreateVariableWithSetGetMacro(ParrentObjectType,MisObjectType);
	misCreateVariableWithSetGetMacro(ParrentUID,misUID);
	misDatasetUIDMacro();
 
public:
	friend class misDataBaseIO;
	//-----------------
	misLandmarkListTypdef    GetPoints(void);
	void                     SetPoints(misLandmarkListTypdef  pointList);

	// Note : it does not return the internal value
    misLandmarkPointStrct*    GetPoint(int id);

	
	misResultCode::ResultIds insertNextPoint(misLandmarkPointStrct newPoint);

	misResultCode::ResultIds DeleteAllPoints(void);
	misResultCode::ResultIds DeletePoint(int id);
	misResultCode::ResultIds DeletePoint(misLandmarkPointStrct point);
    
	misResultCode::ResultIds SwapPoints(int id1, int id2);
	misResultCode::ResultIds UpPointInTheList  (int id);
	misResultCode::ResultIds DownPointInTheList(int id);

	int            FindExactPointID  (misLandmarkPointStrct point);

    misLandmarkPointStrct* FindClosestPoint          (misLandmarkPointStrct point);
	double                 FindClosestPointDistanceTo(misLandmarkPointStrct point);	
	int                    FindClosestPointID        (misLandmarkPointStrct point);

	void           DeepCopy(misLandMarkBase*  newPoint);  
	int            GetNumberOfPoints(void);
     
	misLandMarkBase(void);
	~misLandMarkBase(void);
};




#endif

