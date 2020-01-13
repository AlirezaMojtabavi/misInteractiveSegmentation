#pragma once
#include "serializable.h"
#include "misCTLevelWindowStr.h"
#include "misTryCatchDeserializationMACRO.h"

struct misMRILevelWindowStr :public Serializable
{
	misLevelWindowStr MRIT1;
	misLevelWindowStr MRIT2;

	misMRILevelWindowStr()
	{
		this->Reset();
	};
	void Reset()
	{
		MRIT1.Reset();
		MRIT2.Reset();
	};

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("T1", MRIT1);
		s.serialize("T2", MRIT2);
	}

	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("T1", MRIT1);
		TRYCATCHDESERILIZE("T2", MRIT2);
	}
};
#pragma once
