#pragma once

namespace parcast
{

	class IImageCorrelationSynchronizer
	{
	public:
		virtual void SyncFixedImageWithMovingImage(bool val) = 0;
	};

}