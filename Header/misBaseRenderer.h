#pragma once

class misBaseRenderer:public vtkOpenGLRenderer
{
protected:
	bool m_UsingCulling;
	bool m_SortForALphaRendering;
	double  m_NearPlane;
	double  m_FarPlane;

public:

	misBaseRenderer(void);
	~misBaseRenderer(void);
		bool GetUsingCulling() const;
	void SetUsingCulling(bool val);
	bool GetSortForALphaRendering() const;
	void SetSortForALphaRendering(bool val);
	void SetFarPlane(double val);
	void SetNearPlane(double val);
};
