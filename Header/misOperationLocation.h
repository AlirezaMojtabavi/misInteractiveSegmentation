#pragma once
#include "misRobotCommandElement.h"
#include "misTarget.h"
class misOperationLocation:public  misRobotCommandElement
{
private:
	misTarget    m_TargetDir;
	misTarget      m_Target;
public:
	virtual std::string ToString();

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	misOperationLocation(misTarget  target,misTarget  orientation);
	void SetOrientation(misTarget  orientation);
	void SetTarget(misTarget  target);

	misOperationLocation();
	virtual std::string GetClassType();
	~misOperationLocation(void);
};
