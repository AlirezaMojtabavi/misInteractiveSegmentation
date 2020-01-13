#pragma once


class mis3dRenderer :	public vtkOpenGLRenderer
{
public:
	static mis3dRenderer* New();
	mis3dRenderer(void);
	virtual void ComputeVisiblePropBounds(double   allBounds[6]);

private:
	double   m_MinBoundingLimit, m_MaxBoundingLimit;


};
