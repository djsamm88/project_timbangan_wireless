#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int MAX_STRING_LENGTH;

void setup() {

Serial.begin(9600);
radio.begin();
radio.setAutoAck(false);
radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
radio.startListening();              //This sets the module as receiver
}

void str_replace(char *src, char *oldchars, char *newchars) { // utility string function
  char *p = strstr(src, oldchars);
  char buf[MAX_STRING_LENGTH];
  do {
    if (p) {
      memset(buf, '\0', strlen(buf));
      if (src == p) {
        strcpy(buf, newchars);
        strcat(buf, p + strlen(oldchars));
      } else {
        strncpy(buf, src, strlen(src) - strlen(p));
        strcat(buf, newchars);
        strcat(buf, p + strlen(oldchars));
      }
      memset(src, '\0', strlen(src));
      strcpy(src, buf);
    }
  } while (p && (p = strstr(src, oldchars)));
}

void loop()
{

if (radio.available())              //Looking for the data.
{
  char text[32] = "";                 //Saving the incoming data
  radio.read(&text, sizeof(text));    //Reading the data
  //Serial.print(text);
  //Serial.println("kg");

    str_replace(text, "-", "");
    str_replace(text, " ", "");

    Serial.write(text,32); //Write the serial data

  //Serial.write(strcat( text, " kg \n"));
  //delay(200);
 }
  
  delay(500);
  
}
