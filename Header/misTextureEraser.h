#pragma once
#include "Point.h"
#include "imagetype.h"
enum SegmentMode { Brush, Erase };
class misTextureEraser
{

public:
	misTextureEraser(void);
 	void EraseTexture(misPixelType* Scalars , parcast::Point<int, 3> dimension , double* TableRange , int id );
	void EraseSphereTexture(misPixelType* Scalars, parcast::Point<int, 3> dimension, double* TableRange, int id, SegmentMode segmentMode);
	bool CheckPointInSphere(double cx, double cy, double cz, double x, double y, double z);
	bool CheckPointInCircle(double cx, double cy, double radius, double x, double y);
	void SetEraserPosition(parcast::PointD3 toolTipPosition, parcast::PointD3 spacing);

	void SetEraserSize(int BoxWidth);
	void CreateBrushBox(misPixelType* Scalars, parcast::Point<int, 3> dimension);
	void SetErasingBoxSize(parcast::Point<int, 3> dimension );// eraser size can  is the same as erasingboxsize except for when we get near the borders of the texture, which is when it needs to be refined
private:
	int	m_EraserSize;
	parcast::Point<int, 3>	m_EraserPosition;
	parcast::Point<int, 3>  m_ModifiedEraserPosition;
	parcast::Point<double, 3>	m_EraserSpacing;
	parcast::Point<int, 3>	m_ErasingBoxSize;
	misPixelType* m_SubBox = nullptr;

	SegmentMode m_SegmentMode;
};
