#pragma once

class misClrMarshallingUtil
{
public:
	static std::string ToStdString(System::String^ clrStr)
	{
		msclr::interop::marshal_context context;
		std::string stdStr = context.marshal_as<std::string>(clrStr);
		return stdStr;
	}

	static System::String^ FromStdString(const std::string& stdStr)
	{
		return gcnew System::String(stdStr.c_str());
	}
};

