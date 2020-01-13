#pragma once

class ITransform;

namespace parcast
{

    class ICoordSysCorrelationVariation
    {
    public:
        struct CorrelationStatus
        {
            CorrelationStatus() = default;

            CorrelationStatus(double angularDev, double radialDev, std::unique_ptr<ITransform> correlation, bool isValid)
                : AngularDeviation(angularDev),
                RadialDeviation(radialDev),
                Correlation(std::move(correlation)),
                IsValid(isValid)
            {
            }

            double AngularDeviation = 0;
            double RadialDeviation = 0;
            std::unique_ptr<ITransform> Correlation = nullptr;
            bool IsValid = false;
        };

        virtual ~ICoordSysCorrelationVariation() = default;

        virtual void SetStandardTransform(const std::shared_ptr<ITransform>& matrix) = 0;
        virtual void SetCoordSysIds(const std::string& tool1, const std::string& tool2) = 0;
        virtual CorrelationStatus GetCorrelationStatus() const = 0;
    };

}
