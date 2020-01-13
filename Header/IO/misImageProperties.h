#pragma once

#include "misROI.h"

struct misImageProperties :public Serializable
{
public:
	int		SamplesperPixel;
	int		Rows;
	int		Columns;
	int		BitsAllocated;
	int		BitsStored;
	int		HighBit;
	int		PixelRepresentation;
	tgt::vec3	PixelSpacing; //<float>
	tgt::vec2	Range; 		  //<double>


	misImageProperties();

	void Reset(void);
	void operator =(misImageProperties right);
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);

	void SetImagesNumber(int count);
	int GetImagesNumber() const;
private:
	int     NumberofImages;
};