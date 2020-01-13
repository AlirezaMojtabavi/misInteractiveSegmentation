#pragma once

enum    misSoundAlertTypesNative
{
	// Important Note : this str must be exactly same as misSoundAlertTypes struct, order is too important
	Question,
	WarningSound,
	Information,
	ErrorSound, 
	AppRun,
	AppExit,
	Capture,
	CaptureFailure,
	InCapturingTime,
	TakeSnapshot,
	UnsetAlertType,
	StopPlayingSound,
};