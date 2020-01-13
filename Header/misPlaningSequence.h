#pragma  once

#include "misSpineScrewPlanningSubSeq.h"
#include "misSequenceManager.h"
#include "misStrctTabModel.h" 
#include "VolumeMaker.h"

class misDataSetManager;

class misPlaningSequence :public misSequenceManager
{

public:
	misPlaningSequence(
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		misStrctTabModel tanModel,
		std::shared_ptr<parcast::VolumeMaker> volumeMaker, std::shared_ptr<misSoftwareInformation> softwareInformation);
	void Activated() {};
	misGUIEventConvertor* GetGuiConvertorList();
	std::shared_ptr<misSubSequence> GetPlanning() const { return m_Planning; }
	void SetPlanning(std::shared_ptr<misSubSequence> val) { m_Planning = val; }

private:
	std::shared_ptr<misSubSequence>  m_Planning;
};
