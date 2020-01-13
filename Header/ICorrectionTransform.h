#include "IImage.h"
class ICorrectionTransform
{
	virtual void SetImage(std::shared_ptr<IImage> image ) = 0;
	virtual void SetCorrectionTransformWidget(std::shared_ptr<ICorrectionTransform>) = 0;
};