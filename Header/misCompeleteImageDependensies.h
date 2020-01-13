#pragma once

#include "misImage.h"
#include "ICompeleteImageDependencies.h"
#include "misStringTools.h"

// The class hold properties of visualization and transformation with an image - 
class misCompeleteImageDependencies  : public ICompeleteImageDependencies
{

public:
	misCompeleteImageDependencies (void);;
	const misCompeleteImageDependencies&  operator =(misCompeleteImageDependencies  right);
	std::shared_ptr<IImage> GetImage() const override;
	void SetImage(std::shared_ptr<IImage> val) override;
	std::string GetName() const;
	void SetName(std::string val);
	double GetOpacity() const;
	void SetOpacity(double val);
	misUID GetObjectUID() const;
	void SetObjectUID(misUID val);
	bool GetVisibility() const;
	void SetVisibility(bool val);

private:
	std::shared_ptr<IImage> m_Image;
	std::string name;
	double opacity;
	misUID objectUID;
	bool Visibility;
	
};

