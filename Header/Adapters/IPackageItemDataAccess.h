#pragma once

namespace parcast
{

	class IPackageItemDataAccess
	{
	public:
		virtual ~IPackageItemDataAccess() = default;
		virtual void InsertIfNotExists(const std::string& uid) = 0;
	};

}