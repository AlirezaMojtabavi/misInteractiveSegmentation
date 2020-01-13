#pragma once
#include "serializable.h"
#include "misWindowLevelStr.h"
#include "misEnums.h"
#include "misTryCatchDeserializationMACRO.h"

struct misLevelWindowStr :public Serializable
{
	double Center;
	double Width;

	misLevelWindowStr()
	{
		this->Reset();
	};
	void Reset()
	{
		Center = 0.0;
		Width = 0.0;
	};

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Center", Center);
		s.serialize("Width", Width);
	}

	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("Center", Center);
		TRYCATCHDESERILIZE("Width", Width);
	}
};

struct misCTLevelWindowStr :public Serializable
{
	misLevelWindowStr CTBone;
	misLevelWindowStr CTTumor;
	misLevelWindowStr CTBrain;
	misLevelWindowStr CTBrainSoftTissues;
	misLevelWindowStr CTSpineSoftTissues;

	misCTLevelWindowStr()
	{
		this->Reset();
	};
	void Reset()
	{
		CTBone.Reset();
		CTTumor.Reset();
		CTBrain.Reset();
		CTBrainSoftTissues.Reset();
		CTSpineSoftTissues.Reset();
	};

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Bone", CTBone);
		s.serialize("Tumor", CTTumor);
		s.serialize("Brain", CTBrain);
		s.serialize("BrainSoftTissues", CTBrainSoftTissues);
		s.serialize("SpineSoftTissues", CTSpineSoftTissues);
	}

	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("Bone", CTBone);
		TRYCATCHDESERILIZE("Tumor", CTTumor);
		TRYCATCHDESERILIZE("Brain", CTBrain);
		TRYCATCHDESERILIZE("BrainSoftTissues", CTBrainSoftTissues);
		TRYCATCHDESERILIZE("SpineSoftTissues", CTSpineSoftTissues);
	}
};
