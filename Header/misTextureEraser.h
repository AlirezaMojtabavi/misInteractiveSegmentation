#pragma once
#include "Point.h"
class misTextureEraser
{

public:
	misTextureEraser(void);
 	void EraseTexture(short* Scalars , parcast::Point<int, 3> dimension , double* TableRange , int id );
	void EraseSphereTexture(short* Scalars, parcast::Point<int, 3> dimension, double* TableRange, int id);
	double CheckPointInSphere(double cx, double cy, double cz, double x, double y, double z);
	void SetEraserPosition(parcast::PointD3 toolTipPosition, parcast::PointD3 spacing);

	void SetEraserSize(int BoxWidth);
	void CreateBrushBox(short* Scalars, parcast::Point<int, 3> dimension);
	void SetErasingBoxSize(parcast::Point<int, 3> dimension );// eraser size can  is the same as erasingboxsize except for when we get near the borders of the texture, which is when it needs to be refined
private:
	int	m_EraserSize;
	parcast::Point<int, 3>	m_EraserPosition;
	parcast::Point<double, 3>	m_EraserSpacing;
	parcast::Point<int, 3>	m_ErasingBoxSize;
	short* m_SubBox = nullptr;
};
