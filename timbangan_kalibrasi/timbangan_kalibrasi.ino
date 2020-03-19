#include "HX711.h" //memasukan library HX711

#define DOUT  3 //mendefinisikan pin arduino yang terhubung dengan pin DT module HX711
#define CLK  2 //mendefinisikan pin arduino yang terhubung dengan pin SCK module HX711

HX711 scale(DOUT, CLK);

float calibration_factor = 7050; //nilai kalibrasi ( sesuaikan dari hasil nilai percobaan program sebelumnya

void setup() {
  Serial.begin(9600);
  Serial.println("Memulai program kalibrasi pada sensor berat");
  Serial.println("Pastikan tidak ada beban diatas sensor");
  delay(5000);
  scale.set_scale();
  scale.tare(); // auto zero / mengenolkan pembacaan berat

  long zero_factor = scale.read_average(); //membaca nilai output sensor saat tidak ada beban
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //sesuaikan hasil pembacaan dengan nilai kalibrasi

  Serial.print("Berat: ");
  Serial.print(scale.get_units(), 1);
  Serial.println(" kg");
}
