#pragma once

// Generate a name for Roi image in relation with previous generated names ct-ro-1 ct-roi-2, ...
class misRoiImageNameGenerator
{
public:
	misRoiImageNameGenerator(std::string imageGetPrimeryUID, std::vector<std::string> rOIImagesUID, std::string imageName);
	~misRoiImageNameGenerator(void);
	 
	std::string GetRoiImageName() const;
	 std::string GetPrimaryUID() const;

private:
	std::string m_ImagetPrimeryUID;
	std::vector<std::string> m_ROIImagesUID;
	 std::string m_PrimaryUID;
	 std::string m_ImageName;
	 std::string m_RoiImageName;
};

