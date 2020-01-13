#pragma once

class misCalibrationToolConfiguration
{
public:
	typedef itk::Point<double, 3> PointType;
	typedef itk::Matrix<double, 4, 4> MatrixType;

	enum Axis
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
	};

	void AddPoint(const std::string& pointName, const PointType& coordinates);
	void SetAxisPoints(Axis axis, const std::string& pointName, const std::string& destinationPointName);
	void SetTipCalibrationPoint(const std::string& pointName);
	MatrixType GetTransformMatrix() const;
	std::ostream& PrintInputFormatInfo(std::ostream& oStr) const;
	std::istream& FillFromStream(std::istream& iStr);

private:
	typedef itk::Vector<double, 3> VectorType;

	std::string GetAxisString(Axis axis) const;
	Axis GetAxisEnum(const std::string& axis) const;

	std::map<std::string, PointType> m_Points;
	std::map<Axis, VectorType> m_Axes;
	std::string m_TipCalibrationPointName;
};

std::istream& operator>> (std::istream& is, misCalibrationToolConfiguration& calibToolConf);