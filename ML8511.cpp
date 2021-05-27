#include "ML8511.h"

void ML8511::setup(uint8_t uvout, uint8_t ref_3V3, uint8_t enable){
    _uvout = uvout;
    _ref_3V3 = ref_3V3;
    _enable =  enable;


    pinMode(_uvout, INPUT);
    pinMode(_ref_3V3, INPUT);
    pinMode(_enable, OUTPUT);
}

float ML8511::getUvIntensity(){
  float outputVoltage;
  digitalWrite(_enable, HIGH);
  delay(10);
  uint16_t uvLevel = _averageAnalogRead(_uvout);
  uint16_t refLevel = _averageAnalogRead(_ref_3V3);

  outputVoltage = (5.04 / (float)refLevel) * (float)uvLevel;
  digitalWrite(_enable, LOW);
  return (_mapUVfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0)); 

}

bool ML8511::isLight(){
  float uvIntensity;
  int8_t sunLight = 0;

  for(int8_t x = 0; x < 3; x++){
    uvIntensity = getUvIntensity();
    if(uvIntensity > 0.3){
      sunLight++;
    }
    delay(100);
  }

  if(sunLight > 2){
    return true;
  }else{
    return false;
  }

}


int ML8511::_averageAnalogRead(uint8_t pinToRead)
{
  uint16_t runningValue = 0; 
  int8_t numberOfReadings = 8;
 
  for(int8_t x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  

}


float ML8511::_mapUVfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
