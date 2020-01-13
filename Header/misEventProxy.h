#pragma once
class  misGUIEvent;
class misEventProxy
{
public:
	virtual bool ProcessRequest(misGUIEvent* pEvent)=0;
};
