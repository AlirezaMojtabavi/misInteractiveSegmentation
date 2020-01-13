#pragma once
#include "IPackage3DDataRenderingAdapter.h"
#include "ICheckVolumeRenderingSize.h"

// Due to rendering volume before activating landmark selection and problem is WPF for setting windows size in absolute
// some time when landmark selection is activated the volume rendering parameters is wrong and displayed incorrectly. it seems
// that texture size does not applied correctly. 

class misCheckVolumeRenderingSize : public  ICheckVolumeRenderingSize
{
public:
	misCheckVolumeRenderingSize(std::shared_ptr<IPackage3DDataRenderingAdapter> packageViewer);
	void CheckVolumeRenderingSize() const override;
private:
	std::shared_ptr<IPackage3DDataRenderingAdapter> m_PackageViewer;
};
