#pragma once

#include "ITransformSerializer.h"

namespace parcast
{

    MOCK_BASE_CLASS(MockTransformSerializer, ITransformSerializer)
    {
        MOCK_CONST_METHOD(Deserialize, 1, std::unique_ptr<ITransform>(const std::string& matrix));
        MOCK_CONST_METHOD(Serialize, 1, std::string(const std::shared_ptr<ITransform>& matrix));
    };

}
