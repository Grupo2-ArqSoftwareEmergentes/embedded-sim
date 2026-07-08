#ifndef AIR_QUALITY_STATUS_H
#define AIR_QUALITY_STATUS_H

#include <Arduino.h>

/**
 * @brief Air Quality status levels
 */
enum AirQualityStatus {
    OPTIMAL,
    MODERATE,
    CRITICAL
};

/**
 * @brief Thresholds for air quality evaluation
 */
struct AirQualityThresholds {
    // CO2 thresholds (ppm)
    uint16_t co2ModerateLimit = 1000;   // ASHRAE recommendation
    uint16_t co2CriticalLimit = 1500;   // Poor air quality
    
    // Humidity thresholds (%)
    uint8_t humidityModerateLow = 30;    // Below 30% is too dry
    uint8_t humidityModerateHigh = 70;   // Above 70% promotes mold
    uint8_t humidityCriticalLow = 20;    // Very dry
    uint8_t humidityCriticalHigh = 80;   // Very humid
    
    // Default constructor
    AirQualityThresholds() = default;
    
    // Constructor for custom configuration
    AirQualityThresholds(uint16_t co2Mod, uint16_t co2Crit,
                         uint8_t humModLow, uint8_t humModHigh,
                         uint8_t humCritLow, uint8_t humCritHigh)
        : co2ModerateLimit(co2Mod), co2CriticalLimit(co2Crit),
          humidityModerateLow(humModLow), humidityModerateHigh(humModHigh),
          humidityCriticalLow(humCritLow), humidityCriticalHigh(humCritHigh) {}
};

/**
 * @brief Converts AirQualityStatus enum to human-readable string
 */
inline const char* airQualityLabel(AirQualityStatus status) {
    switch (status) {
        case CRITICAL:
            return "Critical";
        case MODERATE:
            return "Moderate";
        case OPTIMAL:
        default:
            return "Optimal";
    }
}

/**
 * @brief Converts AirQualityStatus to icon
 */
inline const char* airQualityIcon(AirQualityStatus status) {
    switch (status) {
        case CRITICAL:
            return "Critical";
        case MODERATE:
            return "Moderate";
        case OPTIMAL:
        default:
            return "Optimal";
    }
}

#endif // AIR_QUALITY_STATUS_H
