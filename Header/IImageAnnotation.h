#pragma once
class  misImageDataProperties;
 
class IImageAnnotation
{
public:
	virtual void SetTitle(std::string title) = 0;
	virtual void SetRenWinSize(int HorizantalSize, int VerticalSize) = 0;
	virtual void AddDistanceAnnotaion(double distance) = 0;
};
