#pragma once

#include "CompareCollections.h"
#include "misVolumeData.h"

namespace parcast
{

	class misVolumeDataMatcher
	{
	public:
		static void CheckEqual(std::shared_ptr<misVolumeData> a, std::shared_ptr<misVolumeData> b)
		{
			BOOST_CHECK(AreEqual(a, b));
		}

		static bool AreEqual(std::shared_ptr<IVolumeData> a, std::shared_ptr<IVolumeData> b)
		{
			return a->GetUID() == b->GetUID() &&
				a->GetColormaps().size() == b->GetColormaps().size();




			
		}

	private:
	};

}