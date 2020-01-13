/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*      Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*      Claudio Gatti, Ahmad Kolahi, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*    Modified by:
*      Gregory Bootsma, Princess Margaret Hospital - Toronto - Ontario
*
*     Copyright Claron Technology 2000-2003
*
***************************************************************/
#ifndef __MARKERS_H__
#define __MARKERS_H__

#include "Collection.h"
#include "MCamera.h"
#include "Marker.h"
#include "misTestUtility.h"

//An enum for saving status of loaded markers
enum MarkersLoadStatus
{
	LoadedSuccessfully=0,
	LoadingFailed,
	LoadedAlready,
	NotLoaded
};


class Markers
{


public:
	Markers();
	~Markers();	

	void EnableJitterFilter( double JitterFilterCoefficient,bool JitterFilteron_off,int ExtrapolatedFramesNum, double AngularDotProductToleranceDeg );
		
	void clearTemplates();

	//Return the handle to a collection of identified markers by the most recent processed frame. This
	//method returns the handle to an object of collection which contains data information of identified
	//markers, or thaws exception on existence of errors
	mtHandle GetIdentifiedMarkers(MCamera *cam);
	

	void setPredictiveFramesInterleave(int level);
	int getPredictiveFramesInterleave();
	void setTemplateMatchToleranceMM(double newval);
	void KalmanFilterEnabledSet(bool value);
	bool KalmanFilterEnabledGet();
	double getTemplateMatchToleranceMM();
	void setExtrapolatedFrames(int newval);
	int getExtrapolatedFrames();
	void setSmallerXPFootprint(bool newval);
	bool getSmallerXPFootprint();
	double AngularJitterFilterCoefficientGet();
	void  AngularJitterFilterCoefficientSet(double newval);
	int processFrame(MCamera *cam);
	
	mtHandle getTemplateItem(int idx);
	mtCompletionCode getTemplateItemName(int idx, std::string &templateName);
	int GetNumberOfMarkers();

#pragma region AddedByParsiss

//A flag to show if marker templates loaded or not
private: MarkersLoadStatus m_MarkersLoadingStatus;

//Calls Markers_LoadTemplates( markerTemplateDirectory ); if fails to load throws MTCtaskFaildExcetion
//returns the state of marker loading loading
public: MarkersLoadStatus LoadMarkerTemplates(char * markerTemplateDirectory);

//returns status of markers
public: MarkersLoadStatus GetMarkersLoadingStatus();

//A utility to write order of calls
private: misTestUtility m_WriteCallOrder;

#pragma endregion

private:

	char tempString[400];

	

};

#endif
