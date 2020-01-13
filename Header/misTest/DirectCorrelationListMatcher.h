#pragma once

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "ArrayMatcher.h"

namespace parcast
{

	class DirectCorrelationListMatcher
	{
	public:
		DirectCorrelationListMatcher(const std::list<misCoordinateSystemCorrelationTreeManager::DirectCorrelation>& 
			directCorrelation):
			m_DirectCorrelationList(directCorrelation)
		{
		};
			
		bool operator()(const std::list<misCoordinateSystemCorrelationTreeManager::DirectCorrelation>& directCorrelationList)
		{
			return IsEqual(m_DirectCorrelationList, directCorrelationList);
		}
		
		static bool AreDirectCorrelationEqual(
			const misCoordinateSystemCorrelationTreeManager::DirectCorrelation& a,
			const misCoordinateSystemCorrelationTreeManager::DirectCorrelation& b)
		{
			double matrix1[16];
			double matrix2[16];
			a.m_Correlation->Value()->GetMarixElements(matrix1);
			a.m_Correlation->Value()->GetMarixElements(matrix2);
			return a.m_Source == b.m_Source &&
				a.m_Destination == b.m_Destination &&
				std::equal(matrix1, matrix1+16, matrix2) &&
				a.m_Correlation->IsTimed() == b.m_Correlation->IsTimed() &&
				a.m_Correlation->RemainingLifeTime() == b.m_Correlation->RemainingLifeTime();
		}

		static bool IsEqual(
			const std::list<misCoordinateSystemCorrelationTreeManager::DirectCorrelation>&  a,
			const std::list<misCoordinateSystemCorrelationTreeManager::DirectCorrelation>&  b)
		{
			return CompareUnorderedCollections(a, b, AreDirectCorrelationEqual);
		};

	private:
		std::list<misCoordinateSystemCorrelationTreeManager::DirectCorrelation> m_DirectCorrelationList;
	};

}