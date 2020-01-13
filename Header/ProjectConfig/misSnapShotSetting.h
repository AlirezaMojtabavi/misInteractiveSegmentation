#pragma once

#include "serializable.h"

//It will fill with other member, Don't be shocked!
struct misSnapShotSetting:public Serializable
{
	std::string	 SnapShotFileExtension;

	void serialize( XmlSerializer& s ) const;
	void deserialize( XmlDeserializer& s );
};