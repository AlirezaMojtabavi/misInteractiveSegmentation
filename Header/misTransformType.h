#pragma once

// Update misTransformTypeConvertor when changing enum
enum misTransformType
{
	AbsoluteTransform = 0,             // only in tracking view
	RelativeTransform,                 // before registration done
	RegistaredTransform,               // after registration and while use same image in registration and navigation 
	CorrelatedImageRegistredTransform, // use different image in registration and navigation
	unSetTransformType
};

//The utility class convert misTransformType to string  for logging information
class misTransformTypeConvertor
{
public:

	misTransformTypeConvertor (misTransformType type);

	std::string Str();
	
private:
	misTransformType m_Type;
};

