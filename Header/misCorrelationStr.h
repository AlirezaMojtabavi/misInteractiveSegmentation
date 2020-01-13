#pragma once

#include "misTypes.h"

enum misImageToImageCorrStatus
{
	ValidCorr=0,    // green color
	InValidCorr,    // red color
	PartiallyValid, // yellow color
};

struct misCorrelatedImagesStr
{
	misUID FirstImageUID;
	misUID secondImageUID;
};

struct  misImageCorrStatus
{
	misUID                      imageUID;
	misImageToImageCorrStatus   corrStatus;

	misImageCorrStatus()
	{
         this->imageUID.clear();
		 corrStatus = InValidCorr;
	}

	bool operator <( misImageCorrStatus right)
		const {
			int res = this->imageUID.compare(right.imageUID);
			if (res < 0)
				return true;
			else if (res > 0)
				return false;
			else
		 {
			 if (this->corrStatus < right.corrStatus)
				 return true;
			 else
				 return false;
		 }

			return true;
	}

	bool operator ==( misImageCorrStatus right)
		const {
			int res1 = this->imageUID.compare(right.imageUID);
			if ((res1 == 0) && (this->corrStatus == right.corrStatus))
				return true;

			return false;
	}
};

typedef std::vector<misImageCorrStatus>  misImgaeListCorrTypdef;
typedef std::map<misImageCorrStatus,misImgaeListCorrTypdef> misAllCorrStatus;
