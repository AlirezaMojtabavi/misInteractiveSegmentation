#pragma once
class misCommand : public vtkCommand
{
public:
	virtual void SetCaptureLandmark(bool value) = 0;
};
