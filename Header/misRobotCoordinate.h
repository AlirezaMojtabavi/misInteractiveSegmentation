#pragma once
#include "misOrientation.h"
#include "misRobotCommandElement.h"
#include "misTarget.h"
class misRobotCoordinate:public  misRobotCommandElement
{
private:
	misOrientation m_Orientation;
	misTarget      m_Target;
public:
	//returns a full command TIP_COORDINATE_SYSTEM,7,....
	virtual std::string ToString();

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	misRobotCoordinate(misTarget  target,misOrientation  orientation);
	void SetOrientation(misOrientation  orientation);
	void SetTarget(misTarget  target);

	misRobotCoordinate();
	virtual std::string GetClassType();
	~misRobotCoordinate(void);
	
	//returns a double * which so that its first element is x, Second is y and Third element is z
	double * GetPoint();

	//returns a double * which so that its first element is wr, Second is xr, Third element is yr and 4`th element is zr
	double * GetQuaternion();
};

