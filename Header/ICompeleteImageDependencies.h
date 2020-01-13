#pragma once
#include "misStringTools.h"

class IImage;
 
class ICompeleteImageDependencies
{
public:
	virtual std::shared_ptr<IImage> GetImage() const = 0;
	virtual void SetImage(std::shared_ptr<IImage> val) = 0;
	virtual std::string GetName() const = 0;
	virtual void SetName(std::string val) = 0;
	virtual double GetOpacity() const = 0;
	virtual void SetOpacity(double val) = 0;
	virtual misUID GetObjectUID() const = 0;
	virtual void SetObjectUID(misUID val) = 0;
	virtual bool GetVisibility() const = 0;
	virtual void SetVisibility(bool val) = 0;

	~ICompeleteImageDependencies(){}

};
