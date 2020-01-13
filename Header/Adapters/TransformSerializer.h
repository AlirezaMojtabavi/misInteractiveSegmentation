#pragma once

#include "ISplitString.h"
#include "ITransformSerializer.h"

namespace parcast
{

    class ITransformFactory;

    class TransformSerializer : public ITransformSerializer
    {
    public:
        TransformSerializer(
            std::unique_ptr< ISplitString<double> >&& splitString, const std::shared_ptr<ITransformFactory>& xformFactory);

        std::unique_ptr<ITransform> Deserialize(const std::string& serializedXform) const override;
        std::string Serialize(const std::shared_ptr<ITransform>& xform) const override;

    private:
        std::unique_ptr< ISplitString<double> > m_SplitString;
        std::shared_ptr<ITransformFactory> m_XformFactory;
    };

}