#pragma once

namespace parcast
{

	class IPlanDataAdapter
	{
	public:
		virtual void Save() = 0;
		virtual void Load() = 0;
	};

}