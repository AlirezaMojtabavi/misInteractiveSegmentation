#pragma once
class TimeUtils
{
public:
	TimeUtils();
	~TimeUtils();

	static _int64 DifferenceBetweenTwoSystemtime(const SYSTEMTIME st1, const SYSTEMTIME st2);
};

