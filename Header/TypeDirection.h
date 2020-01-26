#pragma once
#include <misViewerTypeDirection.h>
#include <VisualizationGeneralTypes.h>
#include "misPlanarRepresentation.h"

class TypeDirection
{
public:
	static IMAGEORIENTATION GetOrientationDirection(std::shared_ptr<misPlanarRepresentation>) ;
	static misViewerTypeDirection Get(std::shared_ptr<misPlanarRepresentation> );
private:
};

