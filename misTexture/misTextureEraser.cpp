#include "StdAfx.h"
#include "misTextureEraser.h"

#include "misImage.h"
#include "misImageToTextureMap.h"
#include "misOpenglTexture.h"

misTextureEraser::misTextureEraser(void)
{
	m_EraserSize = 9;
	m_ErasingBoxSize[0] = m_ErasingBoxSize[1] = m_ErasingBoxSize[2] = 9;
}
void misTextureEraser::EraseSphereTexture(misPixelType* Scalars, parcast::Point<int, 3> dimension, double* TableRange,
	int id, SegmentMode segmentMode)
{
	m_SegmentMode = segmentMode;
	this->SetErasingBoxSize(dimension);

	if (0 == TableRange)
	{
		cout << "ERROR : MisTextureEraser : the TableRange Pointer is Empty. Eraser cant work!!" << endl;
		_ASSERT(true == false);
	}
	if (0 == Scalars)
	{
		cout << "ERROR : MisTextureEraser : the Scalar Pointer of Image is Empty. Eraser cant work!!" << endl;
		_ASSERT(true == false);
	}
	GLsizei width = m_ErasingBoxSize[0];
	if (width + m_EraserPosition[0] >= dimension[0])
		width = dimension[1] - 1;
	GLsizei height = m_ErasingBoxSize[1];
	if (height + m_EraserPosition[1] >= dimension[1])
		height = dimension[1] - 1;
	GLsizei depth = m_ErasingBoxSize[2];
	if (depth + m_EraserPosition[2] >= dimension[2])
		depth = dimension[2];
	m_ModifiedEraserPosition[0] = m_EraserPosition[0] - ((m_ErasingBoxSize[0]/2) * m_EraserSpacing[0]);
	m_ModifiedEraserPosition[1] = m_EraserPosition[1] - (m_ErasingBoxSize[1] * m_EraserSpacing[1]);
	m_ModifiedEraserPosition[2] = m_EraserPosition[2];
	CreateBrushBox(Scalars, dimension);

	auto MinImage = TableRange[0];
	auto MaxImage = TableRange[1];
	//auto scale = UNSIGNED_SHORT_MAX / (MaxImage - MinImage);
	//auto shift = -(2 * MinImage + 1) / UNSIGNED_SHORT_MAX;

	auto shift = -MinImage / UNSIGNED_SHORT_MAX;
	auto scale = UNSIGNED_SHORT_MAX / (MaxImage - MinImage);
	glPixelTransferf(GL_RED_SCALE, (GLfloat)scale);
	glPixelTransferf(GL_RED_BIAS, (GLfloat)(shift*scale));

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_3D, id);
	glTexSubImage3D(GL_TEXTURE_3D, 0, m_ModifiedEraserPosition[0], m_ModifiedEraserPosition[1],	m_ModifiedEraserPosition[2], width, height,
		depth, GL_RED, GL_UNSIGNED_SHORT, m_SubBox);
	delete m_SubBox;

 
}
bool misTextureEraser::CheckPointInSphere(double cx, double cy, double cz, double x, double y, double z)
{
	double x1 = pow((x - cx), 2);
	double y1 = pow((y - cy), 2);
	double z1 = pow((z - cz), 2);

	return (x1 + y1 + z1) < pow(cx,2) ? true:false;
}
bool misTextureEraser::CheckPointInCircle(double cx, double cy, double radius, double x, double y)
{
	double x1 = pow((x - cx), 2);
	double y1 = pow((y - cy), 2);

	return (x1 + y1) <= pow(radius, 2) ? true : false;
}
void misTextureEraser::SetEraserPosition(parcast::PointD3 toolTipPosition, parcast::PointD3 spacing)
{
	m_EraserSpacing = spacing;
	this->m_EraserPosition[0] = toolTipPosition[0] / spacing[0];
	this->m_EraserPosition[1] = toolTipPosition[1] / spacing[1];
	this->m_EraserPosition[2] = toolTipPosition[2] / spacing[2];
}

void misTextureEraser::SetEraserSize(int BoxWidth)
{
	if (BoxWidth < 2)
	{
		cout << "ERROR : MisTextureEraser : EraserSize is too Small!!!" << endl;
		_ASSERT(true == false);
	}

	this->m_EraserSize = BoxWidth;
}

void misTextureEraser::CreateBrushBox(misPixelType* Scalars, parcast::Point<int, 3> dimension)
{
	bool inSphere = false;
	auto size = m_ErasingBoxSize[0] * m_ErasingBoxSize[1] * m_ErasingBoxSize[2];
	m_SubBox = new misPixelType[size];
	for (int z = 0; z < m_ErasingBoxSize[2]; z++)
		for (int y = 0; y < m_ErasingBoxSize[1]; y++)
			for (int x = 0; x < m_ErasingBoxSize[0]; x++)
			{
				auto a = (m_ErasingBoxSize[0] / 2) * m_EraserSpacing[0];
				auto b = (m_ErasingBoxSize[1] / 2) * m_EraserSpacing[1];
				auto c = (m_ErasingBoxSize[2] / 2) * m_EraserSpacing[2];
				auto realX = x * m_EraserSpacing[0];
				auto realY = y * m_EraserSpacing[1];
				auto realZ = z * m_EraserSpacing[2];

				//inSphere = CheckPointInSphere(a, b, c, realX, realY, realZ);
				inSphere = CheckPointInCircle(a, b, a, realX, realY);
				int imageSize = dimension[0] * dimension[1] * dimension[2];
				int SubBoxIndex = x + y * m_ErasingBoxSize[0] + z * m_ErasingBoxSize[1] * m_ErasingBoxSize[0];
				int ImageIndex = (x + m_ModifiedEraserPosition[0]) + (y + m_ModifiedEraserPosition[1]) * dimension[0] +	round(realZ + m_ModifiedEraserPosition[2]) * dimension[1] * dimension[0];

				if ((x + m_EraserPosition[0] >= 0))
				{
					if ((y + m_EraserPosition[1] >= 0))
					{
						if ((z + m_EraserPosition[2] >= 0))
						{
 
							if (inSphere)
							{
								if (m_SegmentMode == Erase)
								{
									m_SubBox[SubBoxIndex] = 0;
									Scalars[ImageIndex] = 0;
								}
								else
								{
									m_SubBox[SubBoxIndex] = 150;
									Scalars[ImageIndex] = 150;
								}
							}
							else
								m_SubBox[SubBoxIndex] = Scalars[ImageIndex];
						}
					}
				}
			}
}

void misTextureEraser::SetErasingBoxSize(parcast::Point<int, 3> dimension)
{
  	if ((m_EraserPosition[0] + m_EraserSize) > dimension[0])
		m_ErasingBoxSize[0] = dimension[0] - m_EraserPosition[0];
	else
		m_ErasingBoxSize[0] = m_EraserSize;
	if ((m_EraserPosition[1] + m_EraserSize) > dimension[1])
		m_ErasingBoxSize[1] = dimension[1] - m_EraserPosition[1];
	else
		m_ErasingBoxSize[1] = m_EraserSize;

	if ((m_EraserPosition[2] + m_EraserSize) > dimension[2])
		m_ErasingBoxSize[2] = dimension[2] - m_EraserPosition[2];
	else
		m_ErasingBoxSize[2] = m_EraserSize / 6;
}
