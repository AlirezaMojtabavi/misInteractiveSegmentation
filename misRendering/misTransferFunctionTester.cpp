#include "StdAfx.h"
#include "misTransferFunctionTester.h"

misTransferFunctionTester::misTransferFunctionTester(TransFuncIntensity* function)
{
	m_IntensityFunction=function;
}


misTransferFunctionTester::~misTransferFunctionTester(void)
{
}

double misTransferFunctionTester::GetAvergae( misOpenglTexture* texture )
{
	double result=0;
tgt::ivec3  dims=	 texture->getDimensions();
for(size_t i=0;i<dims[0];i++)
	for(size_t j=0;j<dims[1];j++)
		for(size_t k=0;k<dims[2];k++)
		{
		//	tgt::ivec3 index(i,j,k);
			short textvalue=texture->texel<short>(i,j,k);
			result=result+textvalue;
		}
size_t size=dims[0]*dims[1]*dims[2];
result=result/size;
return result;
	
}
