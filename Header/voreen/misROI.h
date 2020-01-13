#pragma once

#include "tgtMacroHeader.h"

//The misRoi class defiens a box shape region of interest  in 3D images
class  misROI
{
public:

	misROI(void);
	misROI(const double* inData, bool isPermanent = false);
	misROI(const int* inExtent, const double* spacing, bool isPermanent = false);
	misROI(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax, bool isPermanent = false);
	~misROI(void);

	const double* getData() const;
	void getData(double *data) const;
	const double& operator [](int index) const;
	double& operator [](int index);
	bool ContainsPoint(double x, double  y, double  z);
	bool IsInitilized() const;
	void Initilized();

	// Determines whether the region of interest should be permanently applied to the image (in addition to the rendered 3D volume).
	bool IsPermanent() const;
	void SetPermanent(bool isPermanent);
	//reset roi bound to start from zero
	void ResetToZeroBase();
	misROI   Intersection(const misROI&  roi) const;
	double GetVolume() const;
	bool IsValid() const;
	void SetValidity(bool value);
	double GetWidth() const; // return xMax - xmin
	double GetHeight() const; // return yMax - yMin
	double GetDepth() const;// return zMax - zMin
	tgt::Vector3d GetMinPoint() const;
	tgt::Vector3d GetMaxPoint() const;
	tgt::Vector3d GetCenter();
	void scale(double scale);

private:
	double  m_Data[6];
	bool m_Initialized;
	bool m_IsPermanent;	// See IsPermanent()
	bool m_ExternalValidity = true;

};

