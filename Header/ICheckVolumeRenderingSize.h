#pragma once

class ICheckVolumeRenderingSize
{
public:
	virtual ~ICheckVolumeRenderingSize() = default;
	virtual void CheckVolumeRenderingSize() const = 0;

};
