#pragma once
#include "misObject.h"
#include "IRepresentation.h"
class misRepresentationContainer : public misOldObject
{
public:
	igstkStandardClassBasicTraitsMacro(misRepresentationContainer, misOldObject);
	igstkNewMacro(Self);
	std::shared_ptr<IRepresentation> GetRepresenation() const;
	void SetRepresenation(std::shared_ptr<IRepresentation> val);
private:
	std::weak_ptr<IRepresentation> m_Represenation;
};

