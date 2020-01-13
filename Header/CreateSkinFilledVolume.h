#pragma once
#include "ISimpleDataPackage.h"
#include "ICreateSkinFilledVolume.h"
namespace  parcast
{
	class CreateSkinFilledVolume : public ICreateSkinFilledVolume
	{
	public:
 		  void CreateTemporaryVolumeDependency(double volumeThreshold, std::shared_ptr<ISimpleDataPackage> package) final;
 	
	};

}