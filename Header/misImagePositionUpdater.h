#pragma once
#include "IImagePositionUpdater.h"
#include "IPackageDataAdapter.h"
#include "BusinessEntities\Point.h"
#include "IPackage2DDataRenderingAdapter.h"

class misImagePositionUpdater : public IImagePositionUpdater
{
public:
	misImagePositionUpdater(std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> packeViewers, double virtaulTipExtend);
 	void UpdatePosition(parcast::Point<double, 3> position) ;
	 

	virtual void SetVirtualTipExtend(double lenght) override;

private:
	double m_VirtaulTipExtend = 0;
	std::vector<std::shared_ptr<IPackage2DDataRenderingAdapter>> m_packageViewers;
};

