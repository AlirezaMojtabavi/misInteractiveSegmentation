#pragma once

struct misToolImageStrct
{
	std::shared_ptr<Gdiplus::Image> MainImage;
	std::vector<std::shared_ptr<Gdiplus::Image>> MarkerImages;

	void Reset();
	misToolImageStrct();
	~misToolImageStrct();
};
