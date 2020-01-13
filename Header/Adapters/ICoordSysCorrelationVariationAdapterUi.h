#pragma once

namespace parcast
{

    class ICoordSysCorrelationVariationAdapterUi
    {
    public:
        virtual ~ICoordSysCorrelationVariationAdapterUi() = default;

        virtual void UpdateTools(const std::string& tool1, const std::string& tool2) = 0;
        virtual void UpdateAngularDeviation(const std::string& angleDegrees) = 0;
        virtual void UpdateRadialDeviation(const std::string& distanceMm) = 0;
    };

}
