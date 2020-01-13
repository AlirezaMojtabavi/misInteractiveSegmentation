#pragma once
class IApplySmoothingDecider
{
public:

	virtual ~IApplySmoothingDecider()
	{
	}
	virtual signed int GetAdaptiveHistoryLength() const= 0;
	virtual void SetAdaptiveHistoryLength(int val) = 0;
	virtual void SetTranslationTolerance(double val) = 0;
	virtual void SetRotationTolerance(double val) = 0;
	virtual void AppendTransform(const tgt::Matrix4d& matrix , double time) = 0;
	virtual void SetHistoryLength(int val) = 0;
	virtual void SetTimeForCheckFixedOrMoving(double val) = 0;
	virtual void SetTimeFixingKernel(double val) = 0;
};

