#pragma once

#include "misCalibrationDataItem.h"

// The ICalibrationDataAnalyzer class provides the abstract interface to classes which determine whether a given set of calibration
// data can be used for calibration using a particular calibration method. Different calibration methods require different 
// data analysis based on their specific data usability criteria. Calibration data elements are relative transforms that
// transform the tool coordinate system to calibrating feature coordinate system on the calibration tool. The elements forming 
// the dataset are added one at a time. 
class ICalibrationDataAnalyzer
{
public:
	virtual ~ICalibrationDataAnalyzer(void)
	{
	}

	// Push a new data element into the data buffer. The contents of the data item are guaranteed not to be changed by the analyzer.
	virtual void Push(std::shared_ptr<const ITransform> element) = 0;
	 
	// Gets the data buffer set as a list which (if data already found to be usable) can be used by the respective calibration
	// method. See IsDataUsable()
	virtual const misCalibrationDataBuffer& GetDataBuffer() const = 0;

	// Clears the data buffer.
	virtual void Clear() = 0;

	// Set/Get Transform list length. This is the maximum number of transform objects that the analyzer will hold and use in 
	// analysis. Usually, this also means the minimum number of transform objects that can be tested for usability.
	virtual void SetDataBufferLength(int length) = 0;
	virtual int GetDataBufferLength() const = 0;

	// This performs the actual analysis on the data set and returns true if the data set, based on the implementation defined
	// usability criteria for the calibration method, can be used for calibration.
	virtual bool IsDataUsable() const = 0;

	// Gets the amount of progress made towards the completion of the analysis as a value between 0 and 1. It is indicative of the
	// fraction of the available length of the data buffer that has been filled with consecutive usable data. Pushing a data item
	// that invalidates the sequence resets the progress value to zero.
	virtual double GetCurrentProgress() const = 0;
};
