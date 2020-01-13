/*
 *  
 *  $Id: dicomfindassociation.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *  Code adapted from Aeskulap
 *
 */
#pragma once
#include "dicomassociation.h"
#include <api/dicom/imodelodicom.h>

class FindAssociation : public Association {
public:
	
	typedef enum FindRootQueryRetrieveInformationModel
	{
		FRQRIM_Patient = 0,
		FRQRIM_Study,
		FRQRIM_PatientStudyOnly,
		FRQRIM_WorkListInformation,
		FRQRIM_GeneralPurposeWorklist,
		FRQRIM_ProtocolInformation,
		FRQRIM_ModalityWorklist
	} FindRootQueryRetrieveInformationModel;
	
	/**
	 Constructors
	 */
	FindAssociation(const std::string& ambitolog);
	
	virtual ~FindAssociation();
	
	/* Find Root Query Retrieve InformationModel */
	void SetFindRootQueryRetrieveInformationModel(FindRootQueryRetrieveInformationModel frqi)
	{
		switch (frqi) {
			case FRQRIM_Patient:
				Association::m_abstractSyntax = (char *) UID_FINDPatientRootQueryRetrieveInformationModel;
				break;
			case FRQRIM_Study:
				Association::m_abstractSyntax = (char *) UID_FINDStudyRootQueryRetrieveInformationModel;
				break;
			case FRQRIM_WorkListInformation:
				Association::m_abstractSyntax = (char *) UID_FINDModalityWorklistInformationModel;
				break;
			case FRQRIM_GeneralPurposeWorklist:
				Association::m_abstractSyntax = (char *) UID_FINDGeneralPurposeWorklistInformationModel;
				break;
			case FRQRIM_ProtocolInformation:
				Association::m_abstractSyntax = (char *) UID_FINDHangingProtocolInformationModel;
				break;
			case FRQRIM_ModalityWorklist:
				Association::m_abstractSyntax = (char *) UID_FINDModalityWorklistInformationModel;
				break;
			default:
				throw std::exception();
		}
	}

	void SetAbstractSyntax(const std::string& abstractSyntax)
	{
		Association::m_abstractSyntax = abstractSyntax.c_str();
	}
	
	
	/**
	 Send a query object (C-Find) through association
	 */
	CONDITION SendObject(DcmDataset *dataset);
	
	/**
	 Get the result stack of the last query
	 */
	virtual DcmStack* GetResultStack();
	
	DcmStack CopyResultStack();
	
	/**
	 Delete all objects from the result stack
	 */
	virtual void DeleteResultStack();
	
	/**
	 Set the maximum number of results
	 */
	void SetMaxResults(int max);
	
	/**
	 Get the maximum number of results
	 */
	int GetMaxResults();
	virtual bool isMaxNumberOfResultsReached();
	
protected:
	
	/**
	 Response handler
	 */
	virtual void OnResponseReceived(DcmDataset* response);
	
	/**
	 Protected data
	 */
	DcmStack result;
	
	bool bPushResults;
	
private:
	
	typedef struct _FindCallbackInfo {
		FindAssociation* pCaller;
		T_ASC_Association* assoc;
    } FindCallbackInfo;
	
	/**
	 C-Find service class user
	 */
	CONDITION findSCU(T_ASC_Association * assoc, DcmDataset * query);
	
	/**
	 Callback function for C-Find service class user
	 */
	static void findCallback(void*, T_DIMSE_C_FindRQ*, int responseCount, T_DIMSE_C_FindRSP*, DcmDataset *responseIdentifiers);
	int maxResults;
	
	virtual void OnAddPresentationContext(T_ASC_Parameters* params);
	
};
