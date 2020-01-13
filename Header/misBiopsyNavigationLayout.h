
#include "INavigationLayoutFactory.h"
 

class misBiopsyNavigationLayout: public INavigationLayoutFactory
{
public:
	std::shared_ptr<IGroupViewerSetting> GetLayout() const override;
	std::shared_ptr<IGroupViewerSetting> GetLayoutFromFile(const std::string& layoutName) const override;
};
