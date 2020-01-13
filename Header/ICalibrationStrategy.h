#pragma once

#include "ITransform.h"
#include "misCalibrationDataItem.h"

// The ICalibrationStrategy class provides an abstract interface to classes that apply a calibration strategy to a set of data
// gathered from the tracker. The gathered data is in the form of a list of transforms that hold instantaneous relative position of
// the subject tracking tool (not any of its features) and the calibration reference feature.
class ICalibrationStrategy
{
public:
	// The list of calibration data elements pair -transformations of (tool - calibrator) that must be near to each other by a specified distance
	virtual void SetDataBuffer(const misCalibrationDataBuffer& buffer) = 0;
	virtual const misCalibrationDataBuffer& GetDataBuffer() const = 0;

	// Gets the calibration transform computed using the implementation defined algorithm.
	virtual std::shared_ptr<ITransform> GetCalibrationTransform() const = 0;

	virtual ~ICalibrationStrategy(void) { }
};