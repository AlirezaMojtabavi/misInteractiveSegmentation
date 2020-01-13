#pragma once

#include "misMacros.h"
#include "misStrctToolAdd.h"
#include "misTrackingManagerTypes.h"


class misPolarisTrackingSubsequence;
class ITrackingSubsequenceViews;
class  misTrackingConfigObserver :	public itk::Command
{
public:

	typedef misTrackingConfigObserver			Self;
	typedef itk::SmartPointer<Self>				Pointer;
	//itk::Command								Superclass;
	static itk::SmartPointer<Self>	 New(void);

	virtual void Execute(const itk::Object *caller, const itk::EventObject & event);
	virtual void Execute(itk::Object *caller, const itk::EventObject & event);
	void SetTrackingViewSequence(ITrackingSubsequenceViews* sequence);
};
