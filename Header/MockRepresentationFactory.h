#pragma once
#include "IRepresentationFactory.h"

MOCK_BASE_CLASS(MockRepresentationFactory, IRepresentationFactory)
{
	MOCK_NON_CONST_METHOD(CreateRepresentation, 2, std::shared_ptr<IRepresentation>(IMAGEORIENTATION , misViewerTypeDirection ));

};
