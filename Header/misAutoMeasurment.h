#pragma  once

#include "misMeasurment.h"

class misAutoMeasurment :public misMeasurment
{
public:
	typedef misAutoMeasurment				Self;  
	typedef ::itk::SmartPointer< Self >			Pointer; 
	static Pointer New(void); 

	void SetMeasurmentWidget(); 
	void SetImageOrientation(IMAGEORIENTATION);
	void SetControlToWidget();
	void SetWidgetFirstPoint(double [3]);
private:
	IMAGEORIENTATION					 m_ImageOrientation;
	double								 m_FirstPoint[3];	
	misAutoMeasurment();
	~misAutoMeasurment();
};