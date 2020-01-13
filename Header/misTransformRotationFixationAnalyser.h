#pragma once

#include "ICalibrationDataAnalyzer.h"

// The misTransformRotationFixationAnalyser class is a concrete implementation of ICalibrationDataAnalyzer that performs analysis
// on the given data set to make sure the all the transforms within the input dataset rotate a pair of perpendicular unit vectors
// to unit vectors in space whose orientation remains almost fixed across the whole data set. If the transforms are the relative 
// transform between a navigation tool and a calibration feature, then the relative orientation of the calibrator feature and 
// navigator tool is almost fixed.
class misTransformRotationFixationAnalyser : public ICalibrationDataAnalyzer
{
public:
	// Creates a misTransformRotationFixationAnalyser object and sets the maximum angular deviation, that is the half vertex angle
	// of the cone that all the transformed vectors must fall within for the dataset to be considered usable.
	misTransformRotationFixationAnalyser(double maxAngularDeviation);
	~misTransformRotationFixationAnalyser();
 
	virtual void SetDataBufferLength(int length);
	virtual int  GetDataBufferLength() const;
	
	virtual void Push(std::shared_ptr<const ITransform> transform);
	virtual void Clear();

	virtual bool IsDataUsable() const;
	virtual double GetCurrentProgress() const;
	virtual const misCalibrationDataBuffer& GetDataBuffer() const;

private:
	typedef itk::Vector<double, 3> VectorType;

	const double MaxAngularDeviation;	// See misTransformRotationFixationAnalyser

	// Performs the usability analysis and updates the value of m_IsDataUsable. It is called after a change is made to the 
	// dataset.
	void PerformAnalysis();

	// List of the pair of vectors transformed using each transform offset
	std::list< std::pair<VectorType, VectorType> > m_OffsetVectors;
	
	int m_DataBufferLength;	// See SetTransformListLength()
	misCalibrationDataBuffer m_DataBuffer;	// See GetDataBuffer()

	bool m_IsDataUsable;	// See IsDataUsable()
	double m_Progress;	// GetCurrentProgress()
};

