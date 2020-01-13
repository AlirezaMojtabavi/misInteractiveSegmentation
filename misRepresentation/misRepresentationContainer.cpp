#include "stdafx.h"
#include "..\Header\misRepresentationContainer.h"


 

std::shared_ptr<IRepresentation> misRepresentationContainer::GetRepresenation() const
{
	return m_Represenation.lock();
}

void misRepresentationContainer::SetRepresenation(std::shared_ptr<IRepresentation> val)
{
	m_Represenation = val;
}
