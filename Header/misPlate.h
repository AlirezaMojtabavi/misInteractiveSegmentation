#pragma once

#include "misInternalShape.h"
#include "misShape.h"

class misPlate :
	public misShape
{
public:
	misPlate();
	~misPlate(void);

	void	SetMaxPermittedMeasurementError(double MeasurementError);
	int		IsInShape(const double CapturedPoint[3]);
protected:
private:
	std::vector<misInternalShape> m_InternalRegions;	
	
	double m_MinAcceptableX;
	double m_MaxAcceptableX;

	double m_MinAcceptableY;
	double m_MaxAcceptableY;

	double m_MinAcceptableZ;
	double m_MaxAcceptableZ;

	double m_MaxPermittedMeasurementError;
};

