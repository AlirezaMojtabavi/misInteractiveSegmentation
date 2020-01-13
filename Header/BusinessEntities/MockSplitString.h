#pragma once

#include "ISplitString.h"

namespace parcast
{

    MOCK_BASE_CLASS(MockSplitString_double, ISplitString<double>)
    {
        MOCK_CONST_METHOD(GetNumbers, 2, std::vector<double> (const std::string& stringOfNumbers, char delimiter));
    };

}
