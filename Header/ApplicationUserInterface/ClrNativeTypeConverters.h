#pragma once

#include "DateTime.h"

namespace parcast
{

	namespace ClrNativeTypeConverters
	{

		using namespace System;
		using namespace System::Runtime::InteropServices;

		std::string ToStdString(System::String^ clrStr)
		{
			const char* chars = static_cast<const char*>((Marshal::StringToHGlobalAnsi(clrStr)).ToPointer());
			std::string stdStr = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
			return stdStr;
		}

		System::String^ FromStdString(const std::string& stdStr)
		{
			return gcnew System::String(stdStr.c_str());
		}

		parcast::DateTime FromClrDateTime(System::DateTime^ dateTime)
		{
			return parcast::DateTime(
				dateTime->Year, static_cast<unsigned char>(dateTime->Month), static_cast<unsigned char>(dateTime->Day),
				static_cast<unsigned char>(dateTime->Hour), static_cast<unsigned char>(dateTime->Minute),
				dateTime->Second + static_cast<double>(dateTime->Millisecond) / 1000);
		}

	}

}
