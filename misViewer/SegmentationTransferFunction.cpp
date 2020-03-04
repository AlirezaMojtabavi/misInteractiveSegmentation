#include "stdafx.h"
#include "SegmentationTransferFunction.h"
#include <misImageSlicerAbstract.h>
#include "misTransFunctionBuilder.h"

SegmentationTransferFunction::SegmentationTransferFunction(std::shared_ptr<IImage> image)
{
	auto TextureHandler = misImageToTextureMap::GetInstance();
	auto imageTexture = TextureHandler->LookUpTexture(image);
	const auto TableRange = imageTexture->GetTableRange();

	misTransFunctionBuilder trasferfunction;
	misDoubleColorListTypedef opacityColorMappingLst;
	opacityColorMappingLst[TableRange[0]] = misDoubleColorStruct(0, 0, 0, 0);


	opacityColorMappingLst[0] = misDoubleColorStruct(0, 0, 0, 0);
	opacityColorMappingLst[100] = misDoubleColorStruct(1, 0, 0,1.0);
	opacityColorMappingLst[200] = misDoubleColorStruct(1, 0, 0, 1.0);
	opacityColorMappingLst[300] = misDoubleColorStruct(1, 0, 0, 0);
	opacityColorMappingLst[TableRange[1]] = misDoubleColorStruct(0, 0, 0, 0);
	auto transfunc = trasferfunction.GenerateTransferFunction(opacityColorMappingLst, TableRange);
	transfunc->updateTexture();
	m_TransFuncIntensity = transfunc;
}

std::shared_ptr<TransFuncIntensity> SegmentationTransferFunction::GetTransferFunction()
{
	return  m_TransFuncIntensity;
}
