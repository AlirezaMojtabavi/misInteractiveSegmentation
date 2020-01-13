#pragma once

#include "misTryCatchDeserializationMACRO.h"


struct misTimePassingForActionPropertiesStr:public Serializable
{
	bool    Activation;

	double  MinAcceptebleTime;
	double  MaxAcceptebleTime;

private:
	double TimeForActivation;

public:
	misTimePassingForActionPropertiesStr()
	{
		this->Reset();
	};

	void   SetTimeForActivation(double val)
	{
		if (MinAcceptebleTime > val)
		{
			val = MinAcceptebleTime;
		}
		else if (MaxAcceptebleTime < val)
		{
			val = MaxAcceptebleTime;
		}

		this->TimeForActivation =  val;
	};
	double GetTimeForActivation()
	{
		return this->TimeForActivation;	
	};
	void   Reset()
	{
		Activation = false;
		MinAcceptebleTime = 0.0;
		MaxAcceptebleTime = 0.0;
		TimeForActivation = 1000.0;
	};

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Activation", Activation);
		s.serialize("TimeForActivation", TimeForActivation);
	}

	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("Activation", Activation);
		TRYCATCHDESERILIZE("TimeForActivation", TimeForActivation);
	}
};

struct misToolFixationPropertiesStr:public Serializable
{
	bool    Activation;

	double  MinAcceptebleTime;
	double  MaxAcceptebleTime;
	double  maxMovementAssumeFixTool;

private:
	double TimeForActivation;

public:
	misToolFixationPropertiesStr()
	{
		this->Reset();
	};

	void   SetTimeForActivation(double val)
	{
		if (MinAcceptebleTime > val)
		{
			val = MinAcceptebleTime;
		}
		else if (MaxAcceptebleTime < val)
		{
			val = MaxAcceptebleTime;
		}

		this->TimeForActivation =  val;
	};
	double GetTimeForActivation()
	{
		return this->TimeForActivation;	
	};
	void   Reset()
	{
		Activation = false;
		MinAcceptebleTime = 0.0;
		MaxAcceptebleTime = 0.0;
		maxMovementAssumeFixTool = 0.0;
		TimeForActivation        = 1000.0;
	};


	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Activation", Activation);
		s.serialize("TimeForActivation", TimeForActivation);

		s.serialize("maxMovementAssumeFixTool", maxMovementAssumeFixTool);
	}
	
	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("Activation", Activation);
		TRYCATCHDESERILIZE("TimeForActivation", TimeForActivation);

		TRYCATCHDESERILIZE("maxMovementAssumeFixTool", maxMovementAssumeFixTool);
	}
};