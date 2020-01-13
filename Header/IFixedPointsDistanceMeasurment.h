#pragma once

enum LandmarkStatus;
typedef std::vector<LandmarkStatus> LandmarkStateListTypdef;

class IFixedPointsDistanceMeasurment
{
public:
	virtual void ChangeButton3DMeasurmentState(int buttonNumber) = 0;
	virtual void SetMeasurmentControlPointerPosition(const double* position) = 0;
	virtual std::vector<itk::Point<double, 3>> GetMeasurmentPoints() = 0;
	virtual LandmarkStateListTypdef GetMeasurmentControlStates() = 0;
	virtual void MeasurmentActivationOn() = 0;
	virtual void MeasurmentActivationOff() = 0;
	virtual bool Is3DMeasurmentControlStateActive() = 0;
	virtual bool IsMeasurmentControlPointerPosition(const double* position) = 0;
	virtual int Update3DMeasurmentInformation(bool freezState, bool avigationToolIsVisible, double* position) = 0;
	virtual double Get3DMeasurmentDistance() = 0;
	virtual void Reset() = 0;
};