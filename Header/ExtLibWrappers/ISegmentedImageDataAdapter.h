#pragma once
namespace parcast
{

	class ISegmentedImageDataAdapter
	{
	public:
		virtual void Save() = 0;
		virtual void Load() = 0;

	};
}

 
