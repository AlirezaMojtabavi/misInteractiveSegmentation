#pragma once

#include "ICoordSysCorrelationVariation.h"

namespace parcast
{

    MOCK_BASE_CLASS(MockCoordSysCorrelationVariation, ICoordSysCorrelationVariation)
    {
        MOCK_NON_CONST_METHOD(SetStandardTransform, 1, void(const std::shared_ptr<ITransform>& matrix));
        MOCK_NON_CONST_METHOD(SetCoordSysIds, 2, void(const std::string& tool1, const std::string& tool2));
        MOCK_CONST_METHOD(GetCorrelationStatus, 0, CorrelationStatus());
    };

}
