#pragma once
#include "misTryCatchDeserializationMACRO.h"

struct misfMRIColorTable : public  Serializable
{
	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("RGB", m_RGB);
	}
	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("RGB", m_RGB);
	}
	tgt::vec4 ImageIndexToRGB(int index)
	{
		return m_RGB[index];
	}
	std::vector<tgt::vec4> GetRGB() const { return m_RGB; }
	void SetRGB(std::vector<tgt::vec4> val) { m_RGB = val; }
private:
	std::vector<tgt::vec4> m_RGB;
	
};