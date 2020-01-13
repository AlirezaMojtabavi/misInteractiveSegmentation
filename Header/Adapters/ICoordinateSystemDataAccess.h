#pragma once

namespace parcast
{

	class ICoordinateSystemDataAccess
	{
	public:
		virtual void InsertIfNotExists(const std::string& coordinateSystemUid) = 0;
		virtual void Delete(const std::string& coordinateSystemUid) = 0;

		virtual ~ICoordinateSystemDataAccess() = default;
	};

}