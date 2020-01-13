#pragma once

namespace parcast
{

    class ICoordSysCorrelationVariationAdapter
    {
    public:
        virtual ~ICoordSysCorrelationVariationAdapter() = default;

        virtual void CalibrateNow() = 0;
        virtual void UpdateStatus() = 0;
    };

}
