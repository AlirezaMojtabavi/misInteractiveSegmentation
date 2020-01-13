#pragma once
namespace  parcast
{
class ICreateSkinFilledVolume
{
public:
	virtual ~ICreateSkinFilledVolume() = default;

	virtual void CreateTemporaryVolumeDependency(double volumeThreshold, std::shared_ptr<ISimpleDataPackage> package) = 0;
 
};

	
}
