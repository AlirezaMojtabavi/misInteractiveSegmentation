#pragma   once
#include "misRobotCommandElement.h"

class misTarget:public misRobotCommandElement
{
public:
	double m_x;
	double m_y;
	double m_z;
public:
	void  SetPosition(double x,double y,double z);
	misTarget(double x,double y,double z);
	misTarget(tgt::Vector3d   position);
	misTarget();

	//returns a string containing a point in string format separated by comma, with this order: x,y,z
	virtual std::string ToString();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	//returns "misTarget"
	virtual std::string GetClassType() ;

	//returns X of point
	double GetX();

	//returns Y of point
	double GetY();

	//returns Z of point
	double GetZ();

};