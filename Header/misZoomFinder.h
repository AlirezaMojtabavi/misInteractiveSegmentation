#pragma once

class misZoomFinder
{
public:
	unsigned int FindPreviousZoomPercentage(unsigned int) const;
	unsigned int FindNextZoomPercentage(unsigned int) const;
private:
	std::vector<unsigned int> m_ZoomLookupTable{90, 100, 110, 125, 150, 175, 200, 225, 275, 300, 350, 400, 450, 500, 700, 1000};

 };
	
	

	

	
