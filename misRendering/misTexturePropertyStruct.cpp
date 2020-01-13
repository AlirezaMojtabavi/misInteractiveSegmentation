#include "stdafx.h"
#include "misTexturePropertyStruct.h"

double* misTexturePropertyStruct::GetRealDimension() /*safe to delete return pointer */
{
	double*	RealDimensions=new double[3];
	RealDimensions[0]=(Extent[1]-Extent[0])* Spacing[0];
	RealDimensions[1]=(Extent[3]-Extent[2])* Spacing[1];
	RealDimensions[2]=(Extent[5]-Extent[4])* Spacing[2];
	return  RealDimensions;
}

double* misTexturePropertyStruct::GetRealExtend()
{
	double*	RealExtend=new double[6];
	RealExtend[0]=0;
	RealExtend[1]=(Extent[1]-Extent[0])* Spacing[0];
	RealExtend[2]=0;
	RealExtend[3]=(Extent[3]-Extent[2])* Spacing[1];
	RealExtend[4]=0;
	RealExtend[5]=(Extent[5]-Extent[4])* Spacing[2];
	return  RealExtend;
}

void misTexturePropertyStruct::Reset( void )
{
	Data           =  0 ;
	Format         = -1  ;
	InternalFormat = -1;
	DataType       = 0;
	Filter         = tgt::Texture::Filter::LINEAR;
	TableRange[0] = -1;
	TableRange[0] = -1;
	Origin        = NULL;
	Modality  = NoData;
	Spacing[0] = 0.0;
	Spacing[1] = 0.0;
	Spacing[2] = 0.0;
	BitStored  = -1;
	for(int i=0;i<6;i++)
		Extent[i] = 0 ;
	ScalarType = -1;
}

misTexturePropertyStruct::misTexturePropertyStruct()
{
	Reset();
}

bool misTexturePropertyStruct::IsValid( void )
{
	// TODO : must add more test
	bool res= true;

	if ( (0 == Spacing.x) || (0 == Spacing.y) || (0 == Spacing.z) )
	{
		res = false;
	}
	auto  Dimensions = GetDimensions();
	if ( (0 == Dimensions[0]) || (0 == Dimensions[1]) || (0 == Dimensions[2]) )
	{
		res = false;

	} 
	else
	{
		res = true;
	}
	return res;
}

void misTexturePropertyStruct::SetWindowCenter( double value )
{
	WindowLevel.SetWindowParams(value,  WindowLevel.GetWindowWidth());
}

void misTexturePropertyStruct::SetWindowLevel( double value )
{
	WindowLevel.SetWindowParams(WindowLevel.GetWindowCenter(), value);
}

double misTexturePropertyStruct::GetWindowCenter()
{
	return  WindowLevel.GetWindowCenter();
}

double misTexturePropertyStruct::GetWindowLevel()
{
	return WindowLevel.GetWindowWidth();

}

tgt::ivec3 misTexturePropertyStruct::GetDimensions()
{
	tgt::ivec3 dimensions;
	dimensions[0]=(Extent[1]-Extent[0])+1;
	dimensions[1]=(Extent[3]-Extent[2])+1;
	dimensions[2]=(Extent[5]-Extent[4])+1;
	return  dimensions;
}

const int* misTexturePropertyStruct::GetExtent()
{
	return Extent;
}

void misTexturePropertyStruct::SetExtent( const int* extent )
{
	std::copy(extent, extent + 6 , Extent);
}

misROI misTexturePropertyStruct::GetROI() const
{
	return m_ROI;
}

void misTexturePropertyStruct::SetROI( const misROI& val )
{
	m_ROI = val;
}

void misTexturePropertyStruct::SetTableRane( double* tableRange )
{
	TableRange[0] = tableRange[0];
	TableRange[1] = tableRange[1];
}

double* misTexturePropertyStruct::GetTableRange()
{
	return TableRange;
}



