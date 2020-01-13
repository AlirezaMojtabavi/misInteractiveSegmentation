#ifndef _LevelInformation_h
#define _LevelInformation_h

#include "misTryCatchDeserializationMACRO.h"


struct levelInformation:public Serializable
{
	unsigned int Number_of_Iterations;
	double Learning_Rate;
	int LevelIndex;

	levelInformation()
	{
		Number_of_Iterations = 0;
		LevelIndex = -1;
		Learning_Rate = -1;
	}

	virtual void serialize(XmlSerializer& s) const
	{
		s.serialize("Number_of_Iterations", Number_of_Iterations);
		s.serialize("Learning_Rate", Learning_Rate);
		s.serialize("LevelIndex", LevelIndex);
	}
	virtual void deserialize(XmlDeserializer& s)
	{
		TRYCATCHDESERILIZE("Number_of_Iterations", Number_of_Iterations);
		TRYCATCHDESERILIZE("Learning_Rate", Learning_Rate);
		TRYCATCHDESERILIZE("LevelIndex", LevelIndex);
	}
	void operator =(levelInformation right)
	{
		Number_of_Iterations = right.Number_of_Iterations;
		LevelIndex = right.LevelIndex;
		Learning_Rate = right.Learning_Rate;
	}
};

#endif
