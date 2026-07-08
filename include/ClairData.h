#ifndef CLAIR_DATA_H
#define CLAIR_DATA_H

#include <Arduino.h>
#include "AirQualityStatus.h"

/**
 * @brief Unified data structure for Clair System
 */
struct ClairData {
    // Timestamp
    unsigned long timestamp;
    
    // SCD41 Data
    struct {
        uint16_t co2;
        float temperature;
        float humidity;
        bool valid;
    } airQuality;

    // Air Quality Status
    AirQualityStatus status;
    String statusLabel;
    String statusIcon;

    // NUEVO: Tiempo real formateado
    String timeFormatted;    // "HH:MM:SS" para la medición
    String uptimeFormatted;   // "HH:MM:SS" para el uptime
    
    String country;  // País desde donde se envía
    
    
    // Constructor
    ClairData() {
        timestamp = 0;
        airQuality.co2 = 0;
        airQuality.temperature = 0;
        airQuality.humidity = 0;
        airQuality.valid = false;

        status = OPTIMAL;
        statusLabel = "Optimal";
        statusIcon = "Optimal";

        timeFormatted = "";
        uptimeFormatted = "";
        country = "PERU";
    }
    
    // Evaluate overall air quality status
    void evaluateStatus(const AirQualityThresholds& thresholds = AirQualityThresholds()) {
        if (airQuality.valid && 
             (airQuality.co2 >= thresholds.co2CriticalLimit ||
              airQuality.humidity < thresholds.humidityCriticalLow || 
              airQuality.humidity > thresholds.humidityCriticalHigh)) {
            status = CRITICAL;
            statusLabel = "Critical";
            statusIcon = "Critical";
            return;
        }

        if (airQuality.valid && 
             (airQuality.co2 >= thresholds.co2ModerateLimit ||
              airQuality.humidity < thresholds.humidityModerateLow || 
              airQuality.humidity > thresholds.humidityModerateHigh)) {
            status = MODERATE;
            statusLabel = "Moderate";
            statusIcon = "Moderate";
            return;
        }
        
        // Default: OPTIMAL
        status = OPTIMAL;
        statusLabel = "Optimal";
        statusIcon = "Optimal";
    }
    
    
    // Print all data to Serial
    void print() {
    Serial.println();
    
    // Usar print() + println() para control exacto
    Serial.print("Time:     ");
    Serial.print(timestamp);
    Serial.println(" ms");
    
    //Serial.print("Status:   ");
    //Serial.println(statusLabel.c_str());
    
    if (airQuality.valid) {
        Serial.print("CO2:      ");
        Serial.print(airQuality.co2);
        Serial.println(" ppm");
        
        Serial.print("Temp:     ");
        Serial.print(airQuality.temperature, 1);
        Serial.println(" C");
        
        Serial.print("Humidity: ");
        Serial.print(airQuality.humidity, 1);
        Serial.println(" %");
    }
    Serial.print("Status:   ");
    Serial.println(statusLabel);
    Serial.println();
}
};

#endif // CLAIR_DATA_H
