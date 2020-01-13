#pragma once

namespace parcast
{

	class PackageImageRelMatcher
	{
	public:
		PackageImageRelMatcher(const PackageImageRelationship& data)
			: m_PackageImageRel(data)
		{
		}

		bool operator() (const PackageImageRelationship& other)
		{
			return IsEqual(m_PackageImageRel, other);
		}

		static bool IsEqual(const PackageImageRelationship& a, const PackageImageRelationship& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.ImageOpacity == b.ImageOpacity &&
				a.ImageVisibility == b.ImageVisibility&&
				a.ImageUid == b.ImageUid;
		}

	private:
		const PackageImageRelationship& m_PackageImageRel;
	};
}

