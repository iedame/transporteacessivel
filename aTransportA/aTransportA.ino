#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <RFID.h>
#include <VirtualWire.h>


RFID rfid(10,5); 
SdFat sd;
SFEMP3Shield MP3player;
const int button1 = 14; // Analog 0
const int button2 = 15; // Analog 1
const int button3 = 16; // Analog 2
const int knockSensor = A3;
const int threshold = 1023;
int button1State = 0;
int button2State = 0;
int button3State = 0;
int sensorReading = 0;

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);  
  pinMode(button3, INPUT);
  //vw_set_ptt_inverted(true);  // Required by the RF module ---OBS
  //vw_setup(2000);            // bps connection speed ---OBS
  //vw_set_tx_pin(18);         // RF pin ---OBS
}

void loop()
{
   //Message to send:
   //const char *msg = "HELLO WORLD";
   //vw_send((uint8_t *)msg, strlen(msg));
   //vw_wait_tx();        // We wait to finish sending the message
   //delay(200);         // We wait to send the message again      
   
   // Piezo
   //Serial.print(sensorReading);
   //sensorReading = analogRead(knockSensor);
   //if (sensorReading >= threshold) {
   //Serial.println("Knock!");                   
   //}
   //delay(1000);
                        
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
                        
                        // Button1
                        //button1State = digitalRead(button1);
                        //if (button1State == HIGH) {  
                        //  MP3player.playTrack(1);
                        //  Serial.println("Botao1 pressionado");
                        //} else {
                        //  Serial.println("Botao1 nao pressionado");
                        //}
                        
                        // Button2
                        //button2State = digitalRead(button2);
                        //if (button2State == HIGH) {  
                        //  MP3player.playTrack(2);
                        //  Serial.println("Botao2 pressionado");
                        //}
                        //else {
                        //  Serial.println("Botao2 nao pressionado");
                        //}
                        
                        // Button3
                        //button3State = digitalRead(button3);
                        //if (button3State == HIGH) {  
                        //  MP3player.playTrack(1);
                        //  Serial.println("Botao3 pressionado");
                        //}
                        //else {
                        //  Serial.println("Botao3 nao pressionado");
                        //}
                        
                        delay(1000);
                       
            
          }
          
    }
    
    rfid.halt();
}
