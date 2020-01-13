#pragma once
#include "IToolShapeBuilder.h"
#include <turtle/mock.hpp>

MOCK_BASE_CLASS(MockToolShapeBuilder, IToolShapeBuilder)
{
	MOCK_CONST_METHOD(GetToolRepresentation, 0, std::shared_ptr<IToolRepresentation> () );
	MOCK_NON_CONST_METHOD(SetToolRepresentationParam, 3, void(misToolRepresentationType, const misToolProperties&, bool));
	MOCK_NON_CONST_METHOD(Clear, 0, void());

};
