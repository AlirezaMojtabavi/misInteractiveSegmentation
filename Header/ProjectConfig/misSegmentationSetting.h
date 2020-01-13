#pragma once

#include "serializable.h"

struct misSegmentationSetting:public Serializable
{
	bool   LoggerEnabeld;
	bool   m_UseThreadForSegmentation;
	double m_SegmentedObjectOpacityScale;
	double m_DefaultObjectMargin;

	virtual void serialize( XmlSerializer& s ) const;
	virtual void deserialize( XmlDeserializer& s );
};