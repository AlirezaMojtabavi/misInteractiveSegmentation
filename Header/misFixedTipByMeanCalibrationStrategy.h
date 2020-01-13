#pragma once

#include "ICalibrationStrategy.h"

// The misFixedTipByMean class is a concrete implementation of ITranslationCalibrationStrategy that performs the calibration process
// by calculating the average offset from the reference point (calibration feature) to the static axis coordinate system of the
// subject tool. Also, before performing the computation, it removes marginal data noise. The expected input data set should 
// typically contain a list of transforms that transform a point or vector in the calibration feature coordinate system to its 
// coordinates in the subject tracking tool static axis coordinate system.
class misFixedTipByMeanCalibrationStrategy : public ICalibrationStrategy
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<ITransform> CreateTransform(const double matrixElements[16]) const;
	};

	misFixedTipByMeanCalibrationStrategy(std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());
	~misFixedTipByMeanCalibrationStrategy() { }

	void SetDataBuffer(const misCalibrationDataBuffer& buffer) override;
	std::shared_ptr<ITransform> GetCalibrationTransform() const override;

private:
	typedef itk::Vector<double, 3> VectorType;

	// Computes the calibration transform and stores it in m_CalibrationTransform. It is called after a new dataset is introduced.
	std::shared_ptr<ITransform> ComputeCalibrationTransform(const misCalibrationDataBuffer& buffer);

	// Filter the given list of vector for noises and compute the average of the remaining vectors.
	VectorType NoiseFilterAndComputeAverage( const std::vector<VectorType>& toolOrientations ) const;

	virtual const misCalibrationDataBuffer& GetDataBuffer() const;

	std::shared_ptr<Injector> m_Injector;
	misCalibrationDataBuffer m_Buffer;
	std::shared_ptr<ITransform> m_CalibrationTransform;
};

