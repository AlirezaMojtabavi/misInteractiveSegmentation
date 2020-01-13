#pragma once

#include "misMatrixElement.h"
#include "misTypes.h"

class misOpenglTexture;

class misSelectionElement
{
private:

public:

	misOpenglTexture*    m_Texture;
	misMatrixElement     m_Matirix;
	misSelectionElement();
	~misSelectionElement(void);
};
