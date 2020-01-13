
#include "stdafx.h"
#include  "misConfirmedImageCounter.h"



bool misConfirmedImageCounter::IsThereAnyUnconfirmedImage(std::shared_ptr<ISimpleDataPackage> packge)
{
	auto imageDepList = packge->GetImageDataDependencies();
	auto foundUnonfirmed = std::find_if(imageDepList.cbegin(), imageDepList.cend(), [](const auto& imageItr)
	{
		if (!imageItr->GetImage() || !imageItr->GetImage()->GetConfirmedDirection())
			return true;
		return false;
	});
 
	return  foundUnonfirmed == imageDepList.end();
 

}
