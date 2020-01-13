#pragma once

namespace parcast
{

	class ICoordinateSystemCorrelationsDataAdapter
	{
	public:
		virtual void SaveCorrelations() = 0;
		virtual void LoadCorrelations() = 0;
		virtual ~ICoordinateSystemCorrelationsDataAdapter() {}
	};

}
