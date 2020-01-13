#pragma once

class IVirtualTipSynchronizer
{
public:
	virtual ~IVirtualTipSynchronizer() = default;
	virtual void UpdateVirtualTipLength(double lenght) = 0;
};
