#pragma once
#include "vtkPointWidget.h"
#include "misHeader.h"
#include "VisualizationGeneralTypes.h"
 
class   misPointWidget:public  vtkPointWidget
{
public:

	IMAGEORIENTATION  m_ImageType;

	static misPointWidget* New()
	{
		return new misPointWidget;
	}
	void PlaceWidget()
	{this->Superclass::PlaceWidget();}

	void RemoveInteractor(vtkRenderWindowInteractor *i);

	misPointWidget(void);
	~misPointWidget(void);
	//virtual void PlaceWidget(double bds[6]);
	virtual void PlaceWidget(double xmin, double xmax, double ymin, double ymax, 
		double zmin, double zmax)
	{
		double bound[6];
		bound[0]=xmin;
		bound[1]=xmax;
		bound[2]=ymin;
		bound[3]=ymax;
		bound[4]=zmin;
		bound[5]=zmax;
		vtkPointWidget::PlaceWidget(bound);
	}
};

