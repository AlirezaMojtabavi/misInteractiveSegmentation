#pragma once

#include "ICoordSysCorrelationVariationAdapterUi.h"

namespace parcast
{

    MOCK_BASE_CLASS(MockCoordSysCorrelationVariationAdapterUi, ICoordSysCorrelationVariationAdapterUi)
    {
        MOCK_NON_CONST_METHOD(UpdateTools, 2, void(const std::string& tool1, const std::string& tool2));
        MOCK_NON_CONST_METHOD(UpdateAngularDeviation, 1, void(const std::string& angleDegrees));
        MOCK_NON_CONST_METHOD(UpdateRadialDeviation, 1, void(const std::string& distanceMm));
    };

}
