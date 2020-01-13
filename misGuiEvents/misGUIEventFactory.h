#pragma once

class  misGUIEvent;
class misGUIEventFactory
{
public:
	misGUIEventFactory(void);
	~misGUIEventFactory(void);
		static misGUIEvent*  CreateElement(std::string type);
};

