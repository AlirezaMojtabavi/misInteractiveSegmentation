#pragma once

#include "ICoordSysCorrelationVariationAdapter.h"

class ISettingStorageEditor;

namespace parcast
{

    class ICoordSysCorrelationVariationAdapterUi;
    class ITransformSerializer;
    class ICoordSysCorrelationVariation;

    class CoordSysCorrelationVariationAdapter : public ICoordSysCorrelationVariationAdapter
    {
    public:
        CoordSysCorrelationVariationAdapter(
            const std::string& settingsFilePath,
            std::unique_ptr<ICoordSysCorrelationVariationAdapterUi>&& ui,
            std::unique_ptr<ISettingStorageEditor>&& settingStorage,
            std::unique_ptr<ITransformSerializer>&& xformSerializer,
            std::unique_ptr<ICoordSysCorrelationVariation>&& correlationVar);
        ~CoordSysCorrelationVariationAdapter();

        void CalibrateNow();
        void UpdateStatus();

    private:
        void Initialize();
        static std::string FormatNumber(double number);
        
        template <typename T>
        static inline T RoundToNDecimalPlaces(const T& num, int decimalPlaces)
        {
            auto order = std::pow(10, decimalPlaces);
            return std::round(num * order) / order;
        }

        std::unique_ptr<ICoordSysCorrelationVariationAdapterUi> m_Ui;
        std::unique_ptr<ISettingStorageEditor> m_SettingStorage;
        std::unique_ptr<ITransformSerializer> m_XformSerializer;
        std::unique_ptr<ICoordSysCorrelationVariation> m_CorrelationVar;
        std::string m_SettingsFilePath;

        bool m_IsInitialized = false;
    };

}
