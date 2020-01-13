#pragma once

class misPlaneWidget : public vtkPlaneWidget
{
public:

	static misPlaneWidget*  New();

	 void PlaceWidget(double bds[6]);
	 misPlaneWidget(void);
	~misPlaneWidget(void);
};
