#pragma once

#include "misCorrelationStr.h"
#include "misSimpleDataPackage.h"

class misCompositeDataPackage : public misSimpleDataPackage
{
	friend class misImageContainedPolydataTest;

public:
	misCompositeDataPackage();
	~misCompositeDataPackage();
	misResultCode::ResultIds DeleteImage(misUID imageUID);
	misResultCode::ResultIds ComparePackage(misCorrelatedImagesStr imgesStr);

protected:
	misResultCode::ResultIds AddingValidityStatus(misUID newObjectParrentUID);

};