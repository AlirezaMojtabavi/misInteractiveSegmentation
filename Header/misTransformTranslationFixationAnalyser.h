#pragma once

#include "ICalibrationDataAnalyzer.h"

// The misTransformTranslationFixationAnalyser class is a concrete implementation of ICalibrationDataAnalyzer that performs analysis
// on the given data set to make sure the all the transforms within the dataset translate the origin to a point in space whose 
// offset vector remains almost fixed across the whole data set, e.i., all the offset vectors fit in a sphere of a certain 
// radius (specified through class constructor).
class misTransformTranslationFixationAnalyser : public ICalibrationDataAnalyzer
{
public:
	// Creates misTransformTranslationFixationAnalyser object and sets the maximum deviation, that is the radius of the sphere 
	// where all the offset vectors must fall within for the dataset to be considered usable.
	misTransformTranslationFixationAnalyser(double maxDeviation);
	~misTransformTranslationFixationAnalyser(void);
 
	virtual void SetDataBufferLength(int length);
	virtual int  GetDataBufferLength() const;

	virtual void Push(std::shared_ptr<const ITransform> transform);
	virtual void Clear();

	virtual bool IsDataUsable() const;
	virtual double GetCurrentProgress() const;
	virtual const misCalibrationDataBuffer& GetDataBuffer() const;

private:
	typedef itk::Vector<double, 3> VectorType;

	// Performs the usability analysis and updates the value of m_IsDataUsable. It is called after a change is made to the 
	// dataset.
	void PerformAnalysis();

	const double MaxDeviation;	// See misTransformTranslationFixationAnalyser

	int m_DataBufferLength;	// See SetTransformListLength()
	misCalibrationDataBuffer m_DataBuffer;	// See GetDataBuffer()
	
	// Used for keeping instantaneous values of tool tip position from reference point.
	std::list<VectorType> m_TranslationOffsetVectors;	

	bool m_IsDataUsable;	// See IsDataUsable()
	double m_Progress;	// GetCurrentProgress()
};

