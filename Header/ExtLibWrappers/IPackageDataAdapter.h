#pragma once

namespace parcast
{

	class IPackageDataAdapter
	{
	public:
		virtual void SavePackages() = 0;
		virtual void LoadPackages() = 0;
	};

}
