#pragma once
#include "IPackageDataRenderingAdapter.h"
#include "IOblqueView.h"

class IPackage3DDataRenderingAdapter : public virtual IPackageDataRenderingAdapter, public IOblqueView
{
public:
	virtual void ModifyVolume() = 0;
	virtual std::shared_ptr<IVolume3DRenderer> GetVolumeViewer() = 0;

	~IPackage3DDataRenderingAdapter() = default;
};
