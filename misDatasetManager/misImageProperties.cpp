#include "stdafx.h"
#include "misImageProperties.h"

misImageProperties::misImageProperties()
{
	Reset();
}

void misImageProperties::Reset( void )
{
	SamplesperPixel	 = -1;
	Rows = -1;
	Columns	= -1;
	BitsAllocated = -1;
	BitsStored = -1;
	HighBit = -1;
	PixelRepresentation = -1;
	Range[0] = -1.0;
	Range[1] = -1.0;
	PixelSpacing[0]	= -1.0;
	PixelSpacing[1]	= -1.0;
	PixelSpacing[2]	= -1.0;
}

void misImageProperties::operator=( misImageProperties right )
{
	Range[0] = right.Range[0];
	Range[1] = right.Range[1];
	PixelSpacing[0] = right.PixelSpacing[0];
	PixelSpacing[1] = right.PixelSpacing[1];
	PixelSpacing[2] = right.PixelSpacing[2];
	SamplesperPixel = right.SamplesperPixel;
	Rows = right.Rows;
	Columns	= right.Columns;
	BitsAllocated = right.BitsAllocated;
	BitsStored = right.BitsStored;
	HighBit = right.HighBit;
	PixelRepresentation = right.PixelRepresentation;
	NumberofImages = right.NumberofImages;
}

void misImageProperties::serialize( XmlSerializer& s ) const
{
	s.serialize("SamplesperPixel",SamplesperPixel);
	s.serialize("Rows",Rows);
	s.serialize("Columns",Columns);
	s.serialize("PixelSpacing",PixelSpacing);
	s.serialize("BitsAllocated",BitsAllocated);
	s.serialize("BitsStored",BitsStored);
	s.serialize("HighBit",HighBit);
	s.serialize("PixelRepresentation",PixelRepresentation);
	s.serialize("NumberofImages",NumberofImages);
	s.serialize("Range",Range);
}

void misImageProperties::deserialize( XmlDeserializer& s )
{
	s.deserialize("SamplesperPixel",SamplesperPixel);
	s.deserialize("Rows",Rows);
	s.deserialize("Columns",Columns);
	s.deserialize("PixelSpacing",PixelSpacing); 
	s.deserialize("BitsAllocated",BitsAllocated);
	s.deserialize("BitsStored",BitsStored);
	s.deserialize("HighBit",HighBit);
	s.deserialize("PixelRepresentation",PixelRepresentation);
	s.deserialize("NumberofImages",NumberofImages);
	s.deserialize("Range",Range);
}

void misImageProperties::SetImagesNumber( int count )
{
	NumberofImages = count;
}

int misImageProperties::GetImagesNumber() const
{
	return NumberofImages; 
}
