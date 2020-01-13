#pragma once

namespace parcast
{

	class Color
	{
	public:
		using NormRgbType = std::tuple<double, double, double>;

		static Color FromRgb(unsigned char red, unsigned char green, unsigned char blue);

		Color();

		std::tuple<double, double, double> GetNormRgb() const;

	private:
		Color(double red, double green, double blue, double alpha);
		static double Normalize(unsigned char c);

		double m_Red;
		double m_Green;
		double m_Blue;
		double m_Alpha;
	};

}
