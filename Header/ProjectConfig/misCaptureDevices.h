#pragma once

#include "serializable.h"

enum videoInputType{UNKOWN, VIDEO_PREVIEW, VIDEO_CAPTURE, SONO};

class misCaptureDevices:public Serializable
{

public:

	misCaptureDevices(void);
	~misCaptureDevices(void);

	std::vector<std::string>	m_AllInstalledCaptureDevices;

	std::string			m_EndoscopeCaptureDevice;
	std::string			m_Webcam;

	std::string			m_DefaultStreamType;

	std::string    m_VideoType;

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};

