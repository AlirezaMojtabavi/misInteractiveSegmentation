#include "StdAfx.h"
#include "misCompositeDataPackage.h"

#include "ICoordinateSystemCorrelationManager.h"
#include "misCompeleteImageDependensies.h"
#include "misCompeletePolyDataDependensiesStrct.h"
#include "misDataSetManager.h"
#include "misMathUtils.h"
#include "misStrctDataSets.h"

using namespace std;

misCompositeDataPackage::misCompositeDataPackage(void) 
: misSimpleDataPackage(misDatasetManager::GetInstance()->GetPackagePlanRelRepo())
{
	m_ObjectType         = misCompositePackageType;
}

misCompositeDataPackage::~misCompositeDataPackage(void)
{
}

	
misResultCode::ResultIds   misCompositeDataPackage::AddingValidityStatus( misUID newObjectParrentUID )
{
	// any adding is valid for this package type
	return misResultCode::NoError;
}

misResultCode::ResultIds misCompositeDataPackage::DeleteImage( misUID imageUID )
{
	misResultCode::ResultIds  resultID;
	resultID =	  misResultCode::NoError;
	if (this->m_ImageDataS.empty())
	{
		resultID = misResultCode::ErNoValidPointer;
		return resultID;
	}

	int numberofImages = this->m_ImageDataS.size();


	auto it = remove_if(this->m_ImageDataS.begin(), this->m_ImageDataS.end(), [&] (auto ImageDep )->bool
	{
		bool res = false;
		if (0 == ImageDep->GetObjectUID().compare(imageUID))
		{
			res = true;
		}
		return res;
	});
	
	if (it != this->m_ImageDataS.end())
	{
		this->m_ImageDataS.resize(it- this->m_ImageDataS.begin());
		resultID = misResultCode::NoError;
		return resultID;
	}
	return resultID;
}

misResultCode::ResultIds misCompositeDataPackage::ComparePackage( misCorrelatedImagesStr imgesStr )
{
	misResultCode::ResultIds  resultID = misResultCode::NoError;

	if (m_ImageDataS.size() == 2)
	{
		if ( (imgesStr.FirstImageUID == m_ImageDataS[0]->GetObjectUID()) 
			&& (imgesStr.secondImageUID == m_ImageDataS[1]->GetObjectUID()) )
		{
			resultID =	  misResultCode::ErDuplicatedpackage;
		}
		else if ( (imgesStr.FirstImageUID == m_ImageDataS[1]->GetObjectUID()) 
			&& (imgesStr.secondImageUID == m_ImageDataS[0]->GetObjectUID()) )
		{
			resultID =	  misResultCode::ErDuplicatedpackage;
		}	
	}	
	return resultID;
}

 
