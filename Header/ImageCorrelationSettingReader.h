#pragma once
#include "IImageCorrelationSettingReader.h"

namespace parcast
{

	class ImageCorrelationSettingReader : public IImageCorrelationSettingReader
	{
	public:
		ImageCorrelationSettingReader(const std::string& filePath);
		std::shared_ptr<ImageCorrelationSetting> Read() const override;

	private:
		std::string m_FilePath;
	};

}