#pragma once

#include "serializable.h"

//It will fill with other member, Don't be shocked!
struct misVideoSetting : public Serializable
{
	std::string	 VideoFileExtension;

	void serialize( XmlSerializer& s ) const;
	void deserialize( XmlDeserializer& s );
};