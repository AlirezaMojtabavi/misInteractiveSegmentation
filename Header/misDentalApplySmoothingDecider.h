#pragma once
#include "IAppySmoothingDecider.h"
class misDentalApplySmoothingDecider :public IApplySmoothingDecider
{
public:
 
	signed int GetAdaptiveHistoryLength() const override;


	 virtual void SetTranslationTolerance(double val) override;


	 virtual void SetRotationTolerance(double val) override;


	 virtual void AppendTransform(const tgt::Matrix4d& matrix, double time) override;


	 virtual void SetHistoryLength(int val) override;


	 virtual void SetTimeForCheckFixedOrMoving(double val) override;


	 virtual void SetTimeFixingKernel(double val) override;
 	 void SetAdaptiveHistoryLength(int val) override;

private:
	int m_HistoryLength  = 20;
	int m_AdaptiveHistoryLength = 8;
};

