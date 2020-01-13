#pragma once

#include "IFixedPointsDistanceMeasurment.h"
#include "mis3DMeasurmentControl.h"

class misFixedPointsDistanceMeasurment : public IFixedPointsDistanceMeasurment
{
public:

	void ChangeButton3DMeasurmentState(int buttonNumber) override;
	void SetMeasurmentControlPointerPosition(const double* position) override;
	std::vector<itk::Point<double, 3>> GetMeasurmentPoints() override;
	LandmarkStateListTypdef GetMeasurmentControlStates() override;
	void MeasurmentActivationOn() override;
	void MeasurmentActivationOff() override;
	bool Is3DMeasurmentControlStateActive() override;
	bool IsMeasurmentControlPointerPosition(const double* position) override;
	int Update3DMeasurmentInformation(bool freezState, bool avigationToolIsVisible, double* position) override;
	double Get3DMeasurmentDistance() override;
	void Reset() override;

private:

	LandmarkStateListTypdef GetMeasurementLandamrkState();
	mis3DMeasurmentControl m_3DMeasurmentControl;
};
