#pragma once

class ITransform;

namespace parcast
{

    class ITransformSerializer
    {
    public:
        virtual ~ITransformSerializer() = default;

        virtual std::unique_ptr<ITransform> Deserialize(const std::string& matrix) const = 0;
        virtual std::string Serialize(const std::shared_ptr<ITransform>& matrix) const = 0;
    };

}
