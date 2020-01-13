#pragma once
#include "serializable.h"
#include "misRobotCommandElement.h"
class misOrientation:  public misRobotCommandElement
{
public:

	double m_w;
	double  m_x;
	double m_y;
	double m_z;
public:

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	//returns a string with W of quaternion is the first element
	virtual std::string ToString();

	//returns  std::sting = "misOrientation"
	virtual std::string GetClassType();
	misOrientation(double w,double x,double y , double z);
	misOrientation(tgt::vec3  orientation,float w);
	void SetOrientation(double w,double x,double y , double z);
	misOrientation();

	~misOrientation(void);
};

