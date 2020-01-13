#pragma once

class ISimpleDataPackage;

namespace parcast
{
	class IPackageConfirmer
	{
	public:
		virtual bool IsConfirmed(std::shared_ptr<ISimpleDataPackage> pkg) = 0;
	};
}