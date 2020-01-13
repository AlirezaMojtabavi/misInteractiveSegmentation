#pragma once
class IBackToPanMode
{
public:
	virtual void Update() = 0;
	virtual void SetControlToPan() = 0;
	virtual void ResetGeneralToolbarState() const = 0;

};