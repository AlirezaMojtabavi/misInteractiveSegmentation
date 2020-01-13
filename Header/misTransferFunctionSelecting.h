#pragma once

#include "misColorStruct.h"
#include "misOpenglTexture.h"

class misTransferFunctionSelecting
{
public:

	misTransferFunctionSelecting();
	~misTransferFunctionSelecting();

	void Reset();
	void UpdateTExtureTransferFunctions(misOpenglTexture* pTexture , ImageContainedTransferFuncs3D Tfs);
	misColorStruct GetCorrespondingTransFunColor(misOpenglTexture* pTexture,double intensity);

private:
	std::map<misOpenglTexture* , ImageContainedTransferFuncs3D> m_VolumeMap;
};
