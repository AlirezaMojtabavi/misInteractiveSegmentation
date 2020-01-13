#pragma  once


using namespace System;
using namespace WrapperGUIBase;

public ref class misMessageTypeControler
{
public :

	CommandEnum* messageBoxDefaultButton;

	property bool mustShow
	{
		bool get() { return __mustShow; }
		void set(bool value) { __mustShow = value; }
	}

	property bool needCheckBox
	{
		bool get() { return __needCheckBox; }
		void set(bool value) { __needCheckBox = value; }
	}

	property bool IsExist
	{
		bool get() { return __isExist; }
		void set(bool value) { __isExist = value; }
	}

	property System::String^ messageName
	{
		System::String^ get() { return __messageName; }
		void set(System::String^ value) { __messageName = value; }
	}

	property System::String^ messageValue
	{
		System::String^ get() { return __messageValue; }
		void set(System::String^ value) { __messageValue = value; }
	}

	property misMessageBoxType messageBoxType
	{
		WrapperGUIBase::misMessageBoxType get() { return __messageBoxType; }
		void set(misMessageBoxType value) { __messageBoxType = value; }
	}

	property misMessageBoxButtonsOrder messageBoxButtons
	{
		misMessageBoxButtonsOrder get() { return __messageBoxButtons; }
		void set(misMessageBoxButtonsOrder value) { __messageBoxButtons = value; }
	}

	//property misMessageBoxButtons messageBoxDefaultButton
	//{
	//	misMessageBoxButtons get() { return __messageBoxDefaultButton; }
	//	void set(misMessageBoxButtons value) { __messageBoxDefaultButton = value; }
	//}

	property misMessageBoxSize messageBoxSize
	{
		misMessageBoxSize get() { return __messageBoxSize; }
		void set(misMessageBoxSize value) { __messageBoxSize = value; }
	}

		misMessageTypeControler();

		void Initializer();
		private:

			String^ __messageName;
			String^ __messageValue;

			WrapperGUIBase::misMessageBoxType __messageBoxType;
			misMessageBoxButtonsOrder __messageBoxButtons;
			/*misMessageBoxButtons __messageBoxDefaultButton;*/
			misMessageBoxSize __messageBoxSize;

			bool __needCheckBox;
			bool __mustShow;
			bool __isExist;
};
