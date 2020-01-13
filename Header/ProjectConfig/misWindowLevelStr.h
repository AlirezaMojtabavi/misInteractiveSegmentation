#pragma once

class misWindowLevelStr
{
public:
	misWindowLevelStr();
	misWindowLevelStr(double center, double width);
	double GetWindowCenter() const;
	double GetWindowWidth() const;
	void SetWindowParams(double center, double width);

private: 

	double m_WindowCenter;
	double m_WindowWidth;
 
};
