#pragma once

#include "misDentaLandmarkRegistrationSubSequence.h"

#include "misGroupViewer.h"
#include "misImageToPatientLandmarkBasedRegistation.h"
#include "misLandmarkSelectionSubSequence.h"
#include "misSequenceManager.h"
#include "misToolProperties.h"

class misToolLocator;

//===========================================================================================
// the are two list for the captured points and fixed point
// primary fixed point: contained all points that the user have been selected
// primary capture point: the list that are equal size to the fist fixed point and some of the will be captured by the user

// method: while the number of captured point be more then or equal to 3 the registration calculation will be active
// after pressing calculation, final captured list make by points that have captured status in the primary captured list
// and the final fixed point will be selected form the primary list with same ids of captured points
//these final list will be equal size to at least 3 and at last equal to the primary list size
// 

class  misDentalRegistrationSequence:public misSequenceManager
{

public:
	misDentalRegistrationSequence(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >
		correlationManager, misStrctTabModel tanModel);
	~misDentalRegistrationSequence();
	// Note: create on landmark list in registration manger and pass it to all subsequence only misRegistrationManager is 
	// responsible for deleting it
	// refactor in future to pass value to subsequences 
	bool ProcessRequest(misGUIEvent* pEvent) override;
	void SetNewPackageData(misUID newPackageUid);
	std::shared_ptr<ISimpleDataPackage> CreateTemporaryPackage(std::shared_ptr<IImage> image) const;
	void Reset(void) override;
	void ResetRegistration(void) const;
	void ResetAllRegistration(void);
	void AddCommand(itk::Command*  pCommand) override;
	int   GetMinimumPointForRegistration(void) const;
	void  SetMinimumPointForRegistration(int number) const;
	misGUIEventConvertor* GetGuiConvertorList() override;
	std::vector<std::shared_ptr<ICoordinateSystemRenderer>>
		BuildTrackerToolRepresentation(const misToolProperties &toolProperties, const ICoordinateSystem* coordinateSytem);
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_pLandmarkList;
	std::shared_ptr<misLandmarkSelectionSubSequence> GetLndSelctionSeq() const;
	std::shared_ptr<misDentaLandmarkRegistrationSubSequence>  GetLndRegistrationSeq() const;
	igstk::Landmark3DRegistrationErrorEstimator::ErrorType m_TRE;
	igstk::Landmark3DRegistrationErrorEstimator::ErrorType m_FRE;
	SubTabSelection m_SlectedTab;

private:
	void SetInfoToViewer(const std::shared_ptr<ISimpleDataPackage>& hybridPackage ) const;
	misUID GetDefaultPackageUID();
	void SetLandmarkSelectionSubseqToInitialState(misUID newPackageUID);
	void SetPackageToLandmarkSelectionSubseq(misUID newPackageUID);
	bool InitializeLandmarkSelectionByDefaultPK();
	bool LoadPreviousRegistrationResult();

	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnloadedEvent();

	misSubsequenceLayout m_landMarkRegSubtab;
	std::shared_ptr<INavigationViewersNView>	m_GroupViewer;
	std::string m_CurrentPackagUsed;
	std::shared_ptr<misDentaLandmarkRegistrationSubSequence> m_LndRegistrationSub;	
	std::shared_ptr<misLandmarkSelectionSubSequence>	m_LndSelectionSub;
	std::shared_ptr<IImage>  m_SelectedImageForLandmarkRegistration;
	std::string m_SubsequenceName;
};
