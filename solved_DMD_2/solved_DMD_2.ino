/*
  Use the Marquee function to make an LED-sign type display

  This marquee function scrolls in all directions, random distances for each
  direction. If you edit the code in the "switch" statement below then you can
  make a simpler marquee that only scrolls in one direction.
*/
#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial14.h>
#include <fonts/Arial_Black_16.h>

/* For "Hello World" as your message, leave the width at 4 even if you only have one display connected */
#define DISPLAYS_WIDE 2
#define DISPLAYS_HIGH 2

SoftDMD dmd(DISPLAYS_WIDE,DISPLAYS_HIGH);
DMD_TextBox box(dmd, 0, 16, 32, 64);



  String a;

char mystr[32]; //Initialized variable to store recieved data


// the setup routine runs once when you press reset:
void setup() {
    Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  
  dmd.setBrightness(255);
  dmd.selectFont(Arial14);
  dmd.begin();
  /* TIP: If you want a longer string here than fits on your display, just define the display DISPLAYS_WIDE value to be wider than the
    number of displays you actually have.
   */
  dmd.drawString(5, 2, F("Selamat"));
  dmd.drawString(10, 15, F(" datang "));



  
}




//int phase = 0; // 0-3, 'phase' value determines direction

// the loop routine runs over and over again forever:
void loop() {


        dmd.setBrightness(255);
        dmd.selectFont(Arial_Black_16);

         

          if (Serial.available()) {
            Serial.readBytes(mystr,32); //Read the serial data and store in var
            Serial.println(mystr); //Print data on Serial Monitor
            dmd.begin();
            dmd.drawString(20, 8, mystr);
          }


          
          if(strcmp(mystr, "0.00") == 0 || strcmp(mystr, "0.01") == 0 || strcmp(mystr, "-0.00") == 0 )

          {
            dmd.setBrightness(255);
            dmd.selectFont(Arial14);
            dmd.begin();
            dmd.drawString(10, 2, F("Damanik "));
            dmd.drawString(10, 15, F("Kolam"));
            
          }

        
          delay(500);
}
