#ifndef __misRotationInformation__
#define __misRotationInformation__
enum RotationAxis
{
	xAxis,
	yAxis,
	zAxis
};

struct RotationStrct
{
	RotationAxis m_RotationAxis;
	float m_RotationAngle;
};



enum ViewerIdentifier
{
	ManModel,
	ImageModel
};


struct misRotationInformation
{
	RotationStrct m_RotationInfo;
	ViewerIdentifier m_ViewerInfo;
};


#endif
