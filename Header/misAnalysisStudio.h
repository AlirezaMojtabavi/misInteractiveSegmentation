#pragma  once
#ifndef  __misAnalysisStudio__
#define  __misAnalysisStudio__

#include "misCreateCompositeSubSeq.h"
#include "misImageSegmentationSubSeq.h"
#include "misSequenceManager.h"

class misAnalysisStudio :public misSequenceManager
{
public:
	misAnalysisStudio(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
	                  const misStrctTabModel& tabModel, std::shared_ptr<misSoftwareInformation> softwareInformation);
	misAnalysisStudio(std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		misStrctTabModel tabModel, std::shared_ptr<misRegionGrowing> regionGrowin, std::shared_ptr<misSoftwareInformation> softwareInformation);
	~misAnalysisStudio();

	virtual void UpdateStatus(long long int puls);
	virtual void Activated() {}
	std::shared_ptr<misImageSegmentationSubSeq> GetImageSegmentation() const { return m_ImageSegmentation; }
	std::shared_ptr<misCreateCompositeSubSeq> GetCreateComposite() const { return m_CreateComposite; }
	misGUIEventConvertor* GetGuiConvertorList();

private:
	std::shared_ptr<misImageSegmentationSubSeq> m_ImageSegmentation;
	std::shared_ptr<misCreateCompositeSubSeq> m_CreateComposite;
};
#endif
