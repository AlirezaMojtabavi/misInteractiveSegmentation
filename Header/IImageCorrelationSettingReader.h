#pragma once
#include "misImageCorrelationSetting.h"

namespace parcast
{

	class IImageCorrelationSettingReader
	{
	public:
		virtual std::shared_ptr<ImageCorrelationSetting> Read() const = 0;
	};

}
