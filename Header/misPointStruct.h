//this file generated to test robot. Hence may not need it in the misProject

#pragma once
#include "serializable.h"
class misPointStruct/* :	public Serializable*/
{
public:
	//x,y,z are positions
	//xCoeff,yCoeff,zCoeff are the same m_x,m_y,m_z I mean coefficients which determine the 
	//slope of robot head
	double x,y,z,xCoeff,yCoeff,zCoeff;

	misPointStruct(void);
	~misPointStruct(void);
	/*void serialize(XmlSerializer& s);
	void deserialize(XmlDeserializer& s);*/
	void Set(double X,double Y,double Z,double XCOEFF,double YCOEFF,double ZCOEFF);
};

