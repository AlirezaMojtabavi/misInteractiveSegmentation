#pragma once

public ref class ProcedureChanger
{
public:
	static void Change(
		misProcedureSelection::SelectedProcedure procedure,
		bool dontShowProcedureSelection, System::String^ endoscopeCaptureDevice);
};