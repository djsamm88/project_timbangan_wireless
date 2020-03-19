# project_timbangan_wireless
project timbangan wireless

timbangan wireless component:

# Server:
- arduino 1 -> nrf24l01
- arduino 2 -> DMD2 (P10)
- arduino 1 -> arduino 2 = TX-TR

Wiring : 
arduino 1 -> nrf24l01
 - gnd  -> gnd 
 - 3.3v -> VCC (Perlu tambahan 10mf capasitor dan vcc eksternal)
 - D9   -> CE
 - D10  -> CSN
 - D13  -> SCK
 - D11  -> MOSI
 - D12  -> MISO
 
arduino 2 -> DMD2 (p10)
- D8  -> SCLK
- D9  -> nOE
- D6  -> A
- D7  -> B
- D11 -> R
- D13 -> CKL
- GND -> GND


# Client:
- arduino -> LCD 1602 i2c
- arduino -> HX711
- arduino -> nrf24l01

Wiring :
arduino -> LCD 1602 i2c
- A5 -> SCL
- A4 -> SDA
- 5v -> VCC
- GND -> GND

arduino -> HX711
- GND -> GND
- D3  -> DT
- D2  -> SCK
- 5V  -> VCC

HX711 -> Load Cell
- E+ -> red
- E- -> black
- A- -> white
- A+ -> green

arduino -> nrf24l01
 - gnd  -> gnd 
 - 3.3v -> VCC (Perlu tambahan 10mf capasitor dan vcc eksternal)
 - D9   -> CE
 - D10  -> CSN
 - D13  -> SCK
 - D11  -> MOSI
 - D12  -> MISO

