#pragma once

#include "ITransform.h"

// The misCalibrationDataElement struct is used by the calibration workflow to continuously gather data from the tracker and pass
// them on for data analysis and the main calibration process. It contains instantaneous transforms of the subject tool and the 
// calibration tool captured at the same time.
struct misCalibrationDataElement
{
	misCalibrationDataElement(vtkSmartPointer<vtkTransform> calibrationTool, vtkSmartPointer<vtkTransform> subjectTool)
		: CalibrationToolTransform(calibrationTool), SubjectToolTransform(subjectTool)
	{
	}

	vtkSmartPointer<vtkTransform> CalibrationToolTransform;
	vtkSmartPointer<vtkTransform> SubjectToolTransform;
};

// The collection that is passed on to data analyzers and calibration strategies.
typedef std::list< std::shared_ptr<const ITransform> > misCalibrationDataBuffer;