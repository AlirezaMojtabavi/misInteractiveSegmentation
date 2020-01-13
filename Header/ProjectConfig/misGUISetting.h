#pragma once

#include "serializable.h"

class misGUISetting : public Serializable
{

public:
	bool PPSA;
	bool CheckTaskIsCompeleteForLeaving;
	bool CheckSubSeqActivation;
	bool AutomaticCaptureSnapShot;
	bool ShowConsoleLogWindow;
	bool ShowVTKLogWindow;
	bool showSplashScreen;
	bool EnableExitButton;
	bool showFPSInRenderes;
	//
	
	std::string  InvalidLicenseText;
	 
	misGUISetting(void);
	~misGUISetting(void);

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};
