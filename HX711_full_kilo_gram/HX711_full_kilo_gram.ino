/**
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;


/*************** wireless **********/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
/*************** wireless **********/


/****************** lcd ***************/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
/***************** lcd *****************/

void setup() {

  /************** wireless ***********/
    radio.begin();                  //Starting the Wireless communication
    radio.setAutoAck(false);
    radio.openWritingPipe(address); //Setting the address where we will send the data
    radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
    //radio.setPALevel(RF24_PA_MAX);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
    radio.stopListening();          //This sets the module as transmitter
  
  const char welcome[8]="1=OK";
    radio.write(&welcome, sizeof(welcome));
  /************** wireless ***********/


/**************** lcd ***********/
lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light
//lcd.backlight();// To Power OFF the back light

lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print(" Damanik Kolam "); //You can write 16 Characters per line .
lcd.setCursor(0,1); //Defining positon to write from first row,first column .
lcd.print("Timbangan 1=OK "); //You can write 16 Characters per line .

/**************** lcd ************/


    
  
  Serial.begin(9600);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");

lcd.clear();  
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Mengatur Skala..."); //You can write 16 Characters per line .
lcd.setCursor(0,1); //Defining positon to write from first row,first column .
lcd.print("Otomatis... "); //You can write 16 Characters per line .

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");


lcd.clear();  
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("Jangan ada beban..."); //You can write 16 Characters per line .
lcd.setCursor(0,1); //Defining positon to write from first row,first column .
lcd.print("Atau alat lain"); //You can write 16 Characters per line .


  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  Serial.println("GO");



lcd.clear();  
lcd.setCursor(0,0); //Defining positon to write from first row,first column .
lcd.print("  Go... "); //You can write 16 Characters per line .
lcd.setCursor(0,1); //Defining positon to write from first row,first column .
lcd.print(" Mulai ... "); //You can write 16 Characters per line .

  const char ready[8]="GO";
  radio.write(&ready, sizeof(ready));
  lcd.clear();//Clean the screen
}

void loop() {
  /*
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 2);
*/

float a = scale.get_units(10)/168;
float b = a * 1000;
float c = b/1000;
Serial.print(c); //scale.get_units() returns a float

// c akan dikirim
Serial.println(" kg");

/******** wireless ******/
const char text[8];
dtostrf(c, 6, 2, text); // Leave room for too large numbers!

radio.write(&text, sizeof(text));
//radio.write(&c, sizeof(c));

Serial.println(text);
/********** wireless *********/


/************* lcd ************/
lcd.setCursor(0,0); 
lcd.print(" Hasil Timbangan, "); 
lcd.setCursor(0,1); 
lcd.print(text); 
/************ lcd **************/

  scale.power_down();			        // put the ADC in sleep mode
  delay(200);
  scale.power_up();


  
}
