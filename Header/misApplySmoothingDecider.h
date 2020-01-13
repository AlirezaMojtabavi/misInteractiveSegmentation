#pragma once
#include "IAppySmoothingDecider.h"
#include "BusinessEntities\Point.h"

class misApplySmoothingDecider : public IApplySmoothingDecider
{
public:
	void SetTranslationTolerance(double val) override;
	void SetRotationTolerance(double val) override;
	signed int GetAdaptiveHistoryLength() const override;
	virtual void AppendTransform(const tgt::Matrix4d& matrix, double time) override;

 	void SetHistoryLength(int val) override;
 	void SetTimeForCheckFixedOrMoving(double val) override;
 	void SetTimeFixingKernel(double val) override;


	virtual void SetAdaptiveHistoryLength(int val) override;

private:
	bool Moved(const std::pair<tgt::Matrix4d, double>& source, 
		const std::pair<tgt::Matrix4d, double>& desitination) const;
	double m_TranslationTolerance;
	double m_RotationTolerance;
	int m_HistortyLenght = 100;
	double m_TimeForCheckFixedOrMoving = 250;
	double m_TimeFixingKernel = 2000;
	std::deque<std::pair<tgt::Matrix4d, double>> m_ValueHistory;

};

 

