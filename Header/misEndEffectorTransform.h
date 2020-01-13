#pragma once
#include "serializable.h"
#include "misRobotCommandElement.h"
#include "misOrientation.h"
#include "misTarget.h"

class misEndEffectorTransform: public misRobotCommandElement
{
private:
	misOrientation m_Orientation;
	misTarget      m_Target;
public:
	misEndEffectorTransform(misTarget  target,misOrientation  orientation);
	misEndEffectorTransform();
	~misEndEffectorTransform(void);

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	virtual std::string ToString();
	virtual std::string GetClassType();

	void	SetEndEffectorTransform(misTarget  target,misOrientation  orientation);
};
