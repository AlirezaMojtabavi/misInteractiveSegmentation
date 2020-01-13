#pragma once

struct sqlite3_stmt;

namespace parcast
{

	template<typename T1, typename T2, typename Comp = std::equal_to<>>
	bool CompareUnorderedCollections(
		const T1& collA, const T2& collB, Comp compare = Comp())
	{
		if (std::size(collA) != std::size(collB))
			return false;

		for (auto& elemFromA : collA)
		{
			bool elemFromAFoundInB = false;
			for (auto& elemFromB : collB)
			{
				if (compare(elemFromA, elemFromB))
				{
					elemFromAFoundInB = true;
					break;
				}
			}
			if (!elemFromAFoundInB)
				return false;
		}
		return true;
	}

	template<typename T1, typename T2, typename Comp = std::equal_to<>>
	class UnorderedCollectionMatcher
	{
		UnorderedCollectionMatcher(const T1& expected, const Comp& compare = Comp())
			: Expected(expected), 
			CompareFunc(compare) { }

		bool operator() (const T2& received)
		{
			return CompareUnorderedCollections(Expected, received);
		}

	private:
		const T1 Expected;
		const Comp CompareFunc;
	};

	template<typename Coll, typename Comp>
	bool CompareSqliteStmtRowsToDataCollectionUnordered(
		sqlite3_stmt* stmt, const Coll& dataCollection, Comp compare)
	{
		int numberOfRows = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			bool rowDataFoundInCollection = false;
			for (const auto& elemFromColl : dataCollection)
			{
				if (compare(stmt, elemFromColl))
				{
					rowDataFoundInCollection = true;
					break;
				}
			}
			if (!rowDataFoundInCollection)
				return false;
			++numberOfRows;
		}
		return numberOfRows == dataCollection.size();
	}

	template<typename CollT1, typename CollT2, typename Comp = std::equal_to<>>
	bool IsCollectionSubSetOf(const CollT1& superset, const CollT2& subset, Comp compare = Comp())
	{
		for (auto const& subsetElem : subset)
		{
			auto found = std::find_if(std::cbegin(superset), std::cend(superset),
				[&compare, &subsetElem](auto const& supersetElem) { return compare(supersetElem, subsetElem); });
			if (found == std::cend(superset))
				return false;
		}
		return true;
	}


	template<typename SubCollT1, typename SuperCollT2, typename Comp = std::equal_to<>>
	class CollectionIsSupersetMatcher
	{
	public:
		CollectionIsSupersetMatcher(const SubCollT1& expectedSubset, const Comp& compare = Comp())
			: ExpectedSubset(expectedSubset),
			CompareFunc(compare) { }

		bool operator() (const SuperCollT2& receivedSuperset)
		{
			return IsCollectionSubSetOf(receivedSuperset, ExpectedSubset);
		}

	private:
		const SubCollT1 ExpectedSubset;
		const Comp CompareFunc;
	};

	class CompareUnorderedPair
	{
	public:

		template<class T>
		static bool CheckEqual(const std::pair<T, T>& a, const std::pair<T, T>& b)
		{
			return (a.first == b.first && a.second == b.second) ||
				(a.first == b.second && a.second == b.first);
		}
	};
}