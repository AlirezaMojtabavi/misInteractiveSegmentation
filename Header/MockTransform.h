#pragma once

#include "ITransform.h"

MOCK_BASE_CLASS(MockTransform, ITransform)
{
    using VectorType = parcast::Vector<double, 3>;
    MOCK_NON_CONST_METHOD(Concatenate, 1, void (std::shared_ptr<const ITransform> otherTrans));
    MOCK_NON_CONST_METHOD(Decatenate, 0, void ());
    MOCK_CONST_METHOD(GetNumberOfConcatTransforms, 0, int ());
    MOCK_CONST_METHOD(GetInverse, 0, std::shared_ptr<ITransform> ());
    MOCK_CONST_METHOD(Clone, 0, std::shared_ptr<ITransform> ());
    MOCK_CONST_METHOD(GetMarixElements, 1, void (double matrixElements[16]));
    MOCK_CONST_METHOD(GetTranslation, 0, std::shared_ptr<ITransform>());
    MOCK_CONST_METHOD(GetRotation, 0, std::shared_ptr<ITransform>());
    MOCK_CONST_METHOD(GetTVec, 0, VectorType());
    MOCK_CONST_METHOD(GetRVec, 0, VectorType());
};