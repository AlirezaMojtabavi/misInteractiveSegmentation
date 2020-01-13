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
#ifndef __CAMERA_H__
#define __CAMERA_H__

class MCamera
{
public:
	MCamera(mtHandle handle = 0);
	~MCamera();

	//bool RawBufferValid();
	//unsigned char **RawBufferAddr();
	int getXRes();
	int getYRes();
	int getSerialNum();
	int getBitsPerPixel();
	double getFrameTime();
	int getNumOfFramesGrabbed();

	double getShutterTime();
	int setShutterTime(double sh);
	double getMaxShutterTime();
	double getMinShutterTime();

	double getShutterTimeLimit();
	void setShutterTimeLimit(double limit);

	double getGain();
	void setGain(double g);
	double getMinGain();
	double getMaxGain();

	double getGainLimit();
	void setGainLimit(double limit);

	mtMeasurementHazardCode getThermalHazard(); 

	double getDBGain();

	double getExposure();
	void setExposure(double e);
	double getMinExposure();
	double getMaxExposure();

	int getSensorsNum();

	int getAutoExposure();
	void setAutoExposure(int ae);

	double getLightCoolness();
	void setLightCoolness(double value);
	void AdjustCoolnessFromColorVector(mtHandle ColorVectorHandle);

	bool getImages( unsigned char ***li, unsigned char ***ri);
	bool getHalfSizeImages(unsigned char ***li, unsigned char ***ri, int xRes, int yRes);
	bool getImages3( unsigned char ***li, unsigned char ***ri, unsigned char ***mi);
	bool get24BitImages3( unsigned char ***li, unsigned char ***ri, unsigned char ***mi);
	bool getHalfSizeImages3(unsigned char ***li, unsigned char ***ri, unsigned char ***mi, int xRes, int yRes);
	bool get24BitImages(unsigned char ***li, unsigned char ***ri);

	bool getProjectionOnImage( int image, double XYZ[], double *x, double *y );
	
	// returns true for success
	bool grabFrame(); 

	//returns the handle of camera
	mtHandle Handle();
	void HdrEnable(bool HdrEnableStatus);
	void SetMiddleSensorState(bool value );
	bool GetMiddleSensorState( );
	double LuxPerPixelUnitGet();
	void  HistogramEqualizeImagesSet(bool val);
	bool get24BitHalfSizeImages(unsigned char ***li, unsigned char ***ri, int xRes, int yRes);
private:
	mtHandle m_handle;
	bool ownedByMe;
	unsigned char *limage;
	unsigned char *rimage ;
	unsigned char *mimage ;

};

#endif
