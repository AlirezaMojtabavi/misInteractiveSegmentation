#pragma once

#include "CompareCollections.h"
#include "misImageContained.h"
#include "ImageContainedStrctMatcher.h"

namespace parcast
{

	class misImageContainedMatcher
	{
	public:
		static void CheckEqual(std::shared_ptr<IImageContained> a, std::shared_ptr<IImageContained> b)
		{
			BOOST_CHECK(AreEqual(a, b));
		}

		static bool AreEqual(std::shared_ptr<IImageContained> a, std::shared_ptr<IImageContained> b)
		{
			return a->GetUID() == b->GetUID() &&
				a->GetParentImageUID() == b->GetParentImageUID() &&
			parcast::CompareUnorderedCollections(a->GetPolyDataProperties(), b->GetPolyDataProperties(),
				ImagePolyDataContenStrctMatcher::IsEqual);
		}

	private:
		

	};


}
