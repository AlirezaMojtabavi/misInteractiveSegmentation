#pragma once

namespace parcast
{

	class IVolumeDataAdapter
	{
	public:
		virtual void Save() = 0;
		virtual void Load() = 0;
	};

}