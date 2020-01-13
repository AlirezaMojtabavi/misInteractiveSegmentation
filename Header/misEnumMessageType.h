#pragma once
using namespace System;

namespace WrapperGUIBase
{
	public enum class misMessageBoxType
	{
		Question,
		Warning,
		NONE,
		Information,
		Error,
		Success
	};
	public enum class misMessageBoxButtonsOrder
	{
		ok,
		OkCancel,
		YesNo,
		YesNoCancel,
		AbortRetryIgnore,
		RetryCancel
	};

	public enum class misMessageBoxSize
	{
		Small,
		Medium,
		Large
	};

	public enum class misMessageBoxButtons
	{
		Ok,
		Cancel,
		Yes,
		No,
		Abort,
		Retry,
		Ignore,
		None
	};

	public enum class misMessageBoxWindowType
	{
		Simple,
		WithVirtualKey
	};
	

};

