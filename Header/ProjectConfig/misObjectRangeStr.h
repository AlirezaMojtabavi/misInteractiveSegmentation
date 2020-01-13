#pragma once

#include "misImageModalityEnum.h"
#include "misobjectProperitiesEnums.h"
#include "serializable.h"

class misObjectRangeStr:public Serializable
{
public:
	misObjectRangeStr();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	misImageDataModality ImageModality;
	mis3DModelTypes ModelType;
	tgt::Vector2d ValidRange;


};

typedef std::vector<misObjectRangeStr> ObjectRangeListTypdef;
