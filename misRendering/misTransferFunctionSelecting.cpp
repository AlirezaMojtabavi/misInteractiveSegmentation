#include "stdafx.h"
#include "misTransferFunctionSelecting.h"
#include "misOpenglTexture.h"

using std::pair;

misTransferFunctionSelecting::misTransferFunctionSelecting()
{
	this->Reset();
}

misTransferFunctionSelecting::~misTransferFunctionSelecting()
{

}

void misTransferFunctionSelecting::Reset()
{
	m_VolumeMap.clear();
}

void misTransferFunctionSelecting::UpdateTExtureTransferFunctions(misOpenglTexture* pTexture , ImageContainedTransferFuncs3D Tfs)
{
	if ( m_VolumeMap.find(pTexture) == m_VolumeMap.end())
	{		
		m_VolumeMap.insert ( pair<misOpenglTexture*,ImageContainedTransferFuncs3D>(pTexture,Tfs) );	
	}
	else
	{
		m_VolumeMap[pTexture]=Tfs;
	}
}

misColorStruct misTransferFunctionSelecting::GetCorrespondingTransFunColor( misOpenglTexture* pTexture,double intensity )
{
	misColorStruct finalColor;
	tgt::col4 tgtFinalColor;
	finalColor.InVisible();
	tgtFinalColor.r = 0;
	tgtFinalColor.g = 0;
	tgtFinalColor.b = 0;
	tgtFinalColor.a = 0;

	_ASSERT (m_VolumeMap.find(pTexture) != m_VolumeMap.end());
		
	ImageContainedTransferFuncs3D currentTFs = m_VolumeMap[pTexture];

	for(int i = 0; i < currentTFs.size() ;i++)
	{
		if(currentTFs[i].allocatedByte.size() == 0)
		{
			tgtFinalColor = currentTFs[0].transferFunction->getMappingForValue(static_cast<float>(intensity));
			finalColor.red = tgtFinalColor.r;
			finalColor.green = tgtFinalColor.g;
			finalColor.blue = tgtFinalColor.b;
			finalColor.alpha = tgtFinalColor.a;
			return finalColor;
		}

		double minval = pow(2.0, currentTFs[i].allocatedByte[0]);
		double maxExp = static_cast<double> (currentTFs[i].allocatedByte[0] + currentTFs[i].allocatedByte.size());
		double maxval = pow(2.0, maxExp);

		if(intensity > minval && intensity < maxval)
		{
			tgtFinalColor = currentTFs[i].transferFunction->getMappingForValue(static_cast<float>(intensity));
		}
	}
 
	finalColor.red = tgtFinalColor.r;
	finalColor.green = tgtFinalColor.g;
	finalColor.blue = tgtFinalColor.b;
	finalColor.alpha = tgtFinalColor.a;

	return finalColor;
}