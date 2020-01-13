#pragma once

class ISimpleDataPackage;
typedef std::string misUID;
class IPackageTransformUpdater
{
public:
	virtual void UpdateRepresentationTransforms() = 0;
	virtual void SetSceneReferenceAndPackge(misUID val, std::shared_ptr<ISimpleDataPackage> package) = 0;
	virtual misUID GetRefrenceId() const = 0;

};

