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
