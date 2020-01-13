#pragma once

class misVTKMattoTgtMatConvertor
{
public:
	misVTKMattoTgtMatConvertor(void);
	~misVTKMattoTgtMatConvertor(void);
	tgt::Matrix4d misVTKMattoTgtMatConvertor::operator()( vtkSmartPointer<vtkMatrix4x4> transform );
    vtkSmartPointer<vtkMatrix4x4>  misVTKMattoTgtMatConvertor::operator()( tgt::Matrix4d transform );
};
