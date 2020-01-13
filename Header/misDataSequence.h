#pragma  once
#ifndef  __MisDataProcedure__
#define  __MisDataProcedure__

#include "misSequenceManager.h"

#include "misDataCheckingSubSeq.h"
#include "misDataSetUploadinSubSeq.h"
#include "misImageCorrelationSubSeq.h"
#include "misPacsManager.h"

class  misDataSequence :public misSequenceManager
{
public:

	misDataSequence(
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		misStrctTabModel tabModel,
		std::shared_ptr<parcast::IVolumeMaker> volumeMaker, std::shared_ptr<misSoftwareInformation> softwareInformation);

	misDataSequence(std::shared_ptr<misDataSetUploadinSubSeq> dataUploading,
		std::shared_ptr<misDataCheckingSubSeq> dataChecking,
		std::shared_ptr<misImageCorrelationSubSeq> imageCorrelation,
		std::shared_ptr<misPacsManager> pacsmanage, std::shared_ptr<misSoftwareInformation> softwareInformation);

	~misDataSequence();
	std::shared_ptr<misDataSetUploadinSubSeq>  GetDataUploading() const { return m_DataUploading; }
	std::shared_ptr<misDataCheckingSubSeq> GetDataChecking() const { return m_DataChecking; }
	std::shared_ptr<misImageCorrelationSubSeq> GetImageCorrelation() const { return m_ImageCorrelation; }
	std::shared_ptr<misPacsManager> GetPacsExplorer() const { return m_PacsManager; }
	void SetDataUploading(std::shared_ptr<misDataSetUploadinSubSeq> val) { m_DataUploading = val; }
	misGUIEventConvertor*  GetGuiConvertorList();

private:

	std::shared_ptr<misDataSetUploadinSubSeq> m_DataUploading;
	std::shared_ptr<misDataCheckingSubSeq> m_DataChecking;
	std::shared_ptr<misImageCorrelationSubSeq> m_ImageCorrelation;
	std::shared_ptr<misPacsManager> m_PacsManager;

	misTabAndSubTabName* m_TabSubTabDescibtion;
};
#endif
