/* 
    MP8511 UV Sensor
    Tutorial: https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/all
    Datasheet: https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf
    Consumo: 300uA (Ligado), 0.1uA (Desigado)
    PINO ENABLE: (0.3V~4.6V) USE RESISTOR DE PULL-DOWN (10K)
    Examplo: 

    #include <ML8511.h>

    ML8511 ml8511;

    void setup() {
        Serial.begin(9600);
        ml8511.setup(A0, A1, 2);
    }

    void loop() {
        Serial.print(" / UV Intensity (mW/cm^2): ");
        Serial.print(ml8511.getUvIntensity());

        Serial.print(" / is light: ");
        Serial.println(ml8511.isLight());
        delay(1000);
    }


*/

#ifndef __ML8511_H__
#define __ML8511__

#include "Arduino.h"

class ML8511{
    public:
        /**
         * @brief Recebe e configura as portas Analogicas como entrada e a Digital como Saida
         * 
         * @param 
         * - uvout: Recebe a saida do sensor ML8511 (0.99V~2.8V), [Analogica]
         * - ref_3V3: Le a o valor de alimentacao do sensor para ajudar na precisao [Analogica]
         * - enable: Liga(HIGH) e desliga(LOW) o sensor, [DIGITAL]
        **/
        void setup(uint8_t uvout, uint8_t ref_3V3, uint8_t enable);
        /**
         * @brief Analisa a incidencia Solar, retorna TRUE tiver Sol direto e FALSE se for Sombra
         * Le 3 valores de Irradiancia para retornar o  valor
         * Tempo medida: 330ms
         **/
        bool isLight();
        /**
         * @brief Retorna o valor da Irradiancia Solar mW/cm^2, com o valor de _uvout mapeado em _mapUVfloat
         * Tempo medida: 10ms
         **/
        float getUvIntensity();   
    private:
        uint8_t _uvout;
        uint8_t _ref_3V3;
        uint8_t _enable;
        int _averageAnalogRead (uint8_t pinToRead);
        float _mapUVfloat(float x, float in_min, float in_max, float out_min, float out_max);
};
#endif