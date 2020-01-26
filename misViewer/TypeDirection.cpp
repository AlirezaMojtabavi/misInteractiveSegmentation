#include "stdafx.h"
#include "..\Header\TypeDirection.h"
#include "misPlanarRepresentation.h"

 

misViewerTypeDirection TypeDirection::Get(std::shared_ptr<misPlanarRepresentation> pStImage) 
{

	auto orientatiopn = GetOrientationDirection( pStImage);
	switch (orientatiopn)
	{
	case AXIAL:
		return misViewerTypeDirection::AxialDirection;
	case CORONAL:
		return misViewerTypeDirection::CoronalDirection;
	case SAGITTAL:
		return misViewerTypeDirection::SagittalDirection;
	default:
		return misViewerTypeDirection::AxialDirection;
	}

}

IMAGEORIENTATION TypeDirection::GetOrientationDirection(std::shared_ptr<misPlanarRepresentation> pStImage) 
{
 	if (!pStImage)
		return UNKnownDirection;
	return pStImage->GetOrientation();
}
