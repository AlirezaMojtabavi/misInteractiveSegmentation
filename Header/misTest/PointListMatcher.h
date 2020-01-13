#pragma once
namespace parcast
{
	class PointListMathcer
	{
	public:
		PointListMathcer(const std::vector<parcast::Point<double, 3>>& pointList) : m_PointList(pointList)
		{
		}

		static bool IsEqual(const std::vector<Point<double, 3>>& a, const std::vector<Point<double, 3>>& b)
		{
			if (a.size() != b.size())
				return false;

			for (int i = 0; i < a.size(); ++i)
				if ((a[i][0] != b[i][0]) || (a[i][1] != b[i][1]) || (a[i][2] != b[i][2]))
					return false;

			return true;
		}

		bool operator()(const std::vector<parcast::Point<double, 3>>& other)
		{
			return IsEqual(m_PointList, other);
		}

	private:
		const std::vector<parcast::Point<double, 3>> m_PointList;
	};
}