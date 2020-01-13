#pragma once

#include "ICoordSysCorrelationVariation.h"
#include "ICoordinateSystemCorrelationManager.h"

class ITransform;

namespace parcast
{

    class ITransformFactory;

    class CoordSysCorrelationVariation : public ICoordSysCorrelationVariation
    {
    public:
        CoordSysCorrelationVariation(
            const std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> >& correlMgr, 
            const std::shared_ptr<ITransformFactory>& xformFactory);
        ~CoordSysCorrelationVariation();

        void SetStandardTransform(const std::shared_ptr<ITransform>& xform) override;
        void SetCoordSysIds(const std::string& tool1, const std::string& tool2) override;
        CorrelationStatus GetCorrelationStatus() const override;

    private:
        std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelMgr;
        std::shared_ptr<ITransformFactory> m_XformFactory;

        std::string m_Tools[2];
        std::shared_ptr<ITransform> m_StdXform;
    };

}
