#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // or 0x27
void setup() {
lcd.begin(16, 2);
}
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("TEST");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  lcd.setCursor(0, 0);
  lcd.print("   ");
  delay(1000);
}
