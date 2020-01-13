#pragma once
#include "misToolProperties.h"
class IToolRepresentation;

// build a misToolRepresentation data represent a tracker tool  in rendering scene
class IToolShapeBuilder
{
public:
	virtual ~IToolShapeBuilder() = default;

	// create and return a representation used for rendering tracking tool  - call SetToolRepresentationParam before using this
	// method.
	virtual std::shared_ptr<IToolRepresentation> GetToolRepresentation() const = 0;
	
	// Set properties needed for construction of a misToolRepresentation
	virtual void SetToolRepresentationParam(misToolRepresentationType toolType, const misToolProperties& toolProp,
		bool measurementVirtualTipActivation) = 0;
	virtual void Clear() = 0;
};

