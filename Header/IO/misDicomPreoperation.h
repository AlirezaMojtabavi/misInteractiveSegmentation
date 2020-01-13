#pragma once

#include "misDcmtkHeader.h"

class  MISDCMTKEXPORT misDicomPreoperation//: public  itk::Object
{
public:
	misDicomPreoperation(void);
	~misDicomPreoperation(void);
	std::string	UncompressedData(std::string imageName, std::string destination);
	bool    DICOMImagesAreCompressed(std::vector<std::string> imageList);
	bool	DICOMImageIsCompressed(std::string imageAdres);
	void	RequestStop();

private:
	std::vector<std::string> m_DicomImagesSourceDirectories;
	bool	m_CancelReadingSerie;
};

