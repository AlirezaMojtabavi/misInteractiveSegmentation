#pragma once

#include "misPointPropertiesOnReferenceEnum.h"
#include "misProjectSettingMacro.h"
#include "serializable.h"

 typedef tgt::vec3 PointCoordinate;
struct misPointPropertiesOnReference:public Serializable
{
	misPointUsecase		pointUsecase;
	misPointStructure	pointStructure;

	PointCoordinate     pointCoordinate;

	virtual void serialize( XmlSerializer& s ) const;
	virtual void deserialize( XmlDeserializer& s );
};

typedef std::vector<misPointPropertiesOnReference> misPointPropertiesOnReferenceTypedef;