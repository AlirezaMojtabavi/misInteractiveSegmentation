#pragma once

#include "misShape.h"

class misInternalShape :
	public misShape
{
public:
	misInternalShape(double Center[3], double MaxAcceptableMovementX, double MaxAcceptableMovementY, 
		double MaxAcceptableMovementZ, double MaxAcceptableMeasurementError, unsigned ID);
	~misInternalShape(void);

	void	SetMaxPermittedMeasurementError(double MeasurementError);
	int		IsInShape(const double CapturedPoint[3]);

private:
	double m_MinAcceptableX;
	double m_MaxAcceptableX;

	double m_MinAcceptableY;
	double m_MaxAcceptableY;

	double m_MinAcceptableZ;
	double m_MaxAcceptableZ;

	double m_MaxPermittedMeasurementError;
};

