#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <RFID.h>


RFID rfid(10,5); 
SdFat sd;
SFEMP3Shield MP3player;

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
}

void loop()
{
    if (rfid.isCard()) {
      
          Serial.println("Valid card");

          if (rfid.readCardSerial()) {
            
                        Serial.println(" ");
                        Serial.println("Mifare number  : ");
			Serial.print(rfid.serNum[0],DEC);
                        Serial.print(" , ");
			Serial.print(rfid.serNum[1],DEC);
                        Serial.print(" , ");
			Serial.print(rfid.serNum[2],DEC);
                        Serial.print(" , ");
			Serial.print(rfid.serNum[3],DEC);
                        Serial.print(" , ");
			Serial.print(rfid.serNum[4],DEC);
                        Serial.println(" ");

                        MP3player.playTrack(1);
                        delay(10000);
                       
            
          }
          
    }
    
    rfid.halt();
}
