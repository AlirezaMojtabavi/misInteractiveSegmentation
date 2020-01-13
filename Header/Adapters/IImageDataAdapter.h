#pragma once

namespace parcast
{

	class IImageDataAdapter
	{
	public:
		virtual void SaveImages() const = 0;
		virtual void LoadImages() const = 0;
	};

}