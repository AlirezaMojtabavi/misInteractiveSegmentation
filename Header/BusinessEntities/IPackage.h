#pragma once

namespace parcast
{

	// The IPackage class provides the abstract interface to a collection of objects from the treatment solution selected to be
	// used together as a package. Each of the objects included in a package can have other composition properties such as its 
	// additional visual preferences.
	class IPackage
	{
	public:
		virtual void DeletePackage() = 0;

		virtual ~IPackage() { }
	};

}
