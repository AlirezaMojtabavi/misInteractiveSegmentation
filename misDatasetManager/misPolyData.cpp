//jalal
#include "stdafx.h"
#include "misPolyData.h"

#include "misDataSetsUtility.h"
#include "misStringTools.h"

 
misPolyData::misPolyData()
{
//misInstanceClassInitialValueMacro("SurfaceModel");
	m_UIDSetOccurance = 0; 

	this->m_ObjectType = misPolyDataType;
	m_DataObjectUID = misStringTools::GenerateNewUID();

	this->m_ModificationFlag             = true;
	this->m_ModificationFlagBinariesPart = true;
}

misPolyData::~misPolyData()
{

}

void misPolyData::DeepCopy( vtkDataObject *src )
{

	// TODO: uncomplted yet !
	vtkPolyData* tempVtkpolydata;
	tempVtkpolydata = dynamic_cast <vtkPolyData*>(src);

	if (tempVtkpolydata)
	{
		vtkPolyData::DeepCopy(tempVtkpolydata);
	}

	misPolyData* tempMisPolydata;
	tempMisPolydata = dynamic_cast <misPolyData*>(src);

	if (tempMisPolydata)
	{
		//  do not need to fill this item
		this->m_BinaryFileName                 = tempMisPolydata->GetBinaryFileName();
		this->m_Name                           = tempMisPolydata->GetName();

		this->m_DataObjectUID                  = tempMisPolydata->GetObjectUID();	
		this->m_ParentImageUID                 = tempMisPolydata->GetParentImageUID();

		this->m_Color                          = tempMisPolydata->GetColor();
		this->m_volume						   = tempMisPolydata->Getvolume();
		this->m_PolydataType				   = tempMisPolydata->GetPolydataType();
		this->m_RenderingType				   = tempMisPolydata->GetRenderingType();

		this->m_UIDSetOccurance =1;
	}

	this->m_ModificationFlag             = true;
	this->m_ModificationFlagBinariesPart = true;

	//this->CallModificationObserver();

}