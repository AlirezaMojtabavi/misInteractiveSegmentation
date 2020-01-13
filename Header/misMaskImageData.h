#pragma once
#include "misImage.h"
#include "misDatasetMacroes.h"
class misDataBaseIO;

class misMaskImageData :public misImage
{
	friend class misDataBaseIO;
	misUID m_parrentImageUID;

public:
	virtual void     DeepCopy(misImage *src);

	misUID  GetParentImageUID(void);
	static misMaskImageData* New(misUID parrentImageUID);

private:
	misMaskImageData(void);
	~misMaskImageData(void);
};
