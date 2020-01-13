/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*      Shi Sherebrin , Robarts Research Institute - London- Ontario , www.robarts.ca
*      Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*      Claudio Gatti, Ahmad Kolahi, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*     Copyright Claron Technology 2000-2003
*
***************************************************************/


#ifndef __CAMERAS_H__
#define __CAMERAS_H__

#include "MCamera.h"
#include "MisMicronUtilities.h"
#include "misTestUtility.h"

//The handle of this class removed because there is one object of this class which do not need a handle
//the other removed entity is bool ownedByMe;
class Cameras
{
public:
	Cameras();
	~Cameras();

	//returns the only attached camera
	MCamera* getCamera();

	//Attaches the only camera connected to system. returning 1 means the function is done correctly.
	int AttachTheONLYAvailableCamera();
	void setHistogramEqualizeImages(bool on_off);

	//calle mtExit()
	void Detach();

	//Sets an string which contains the full address of camera calibration files
	void SetCameraCalibrationFilesDirectory( std::string directory );

	//Grabs the frame from tracker. returns true for success
	bool grabFrame();

	//returns the number of attached cameras
	inline int  getCount()
	{
		 return m_attachedCamNums;
	};

private:
	//The full address of camera calibration directory
	std::string m_CalibrationDir;

	//The number of cameras attached
	int m_attachedCamNums;
	
	// need to lear how to hide it, and keep same access syntax
	MCamera * m_TheOnlyAttachedCamera;

};

#endif
