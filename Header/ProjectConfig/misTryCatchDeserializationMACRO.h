// A macro to handle try catch in deserialization of Xml files
#pragma once

template <typename T>
void ExceptionHandlingDeserialize(XmlDeserializer& s, const std::string& key, T& data)
{
	try
	{
		s.deserialize(key, data);
	}

	catch (const XmlSerializationNoSuchDataException&)
	{
	}
	catch (const XmlSerializationFormatException&)
	{
	}
}

#define TRYCATCHDESERILIZE(stringKey,data) ExceptionHandlingDeserialize(s, stringKey, data)
#define TRYCATCHDESERILIZE_OLD(stringKey,data) \
{\
	try\
	{\
		s.deserialize(stringKey,data);\
	}\
	catch(const XmlSerializationNoSuchDataException&)\
	{\
		except.what();\
		std::cout<<"Exception occured in : "<<typeid(s).name()<<std::endl;\
	}\
	catch(...)\
	{\
		std::cout<<"Unhandled Exception occured..."<<std::endl;\
	}\
}