#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
#include <RFID.h>
#include <VirtualWire.h>

RFID rfid(10,5);
SdFat sd;
SFEMP3Shield MP3player;

// Buttons pins
const int button1 = 14;
const int button2 = 15;
const int button3 = 16;
// Piezo
const int knockSensor = A3;
const int calibracao = 1023;
// Buttons
int button1State = 0;
int button2State = 0;
int button3State = 0;
int sensorReading = 0;
// Panel
int option = 0;
int validUser = 0;
boolean waiting = false;

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
  // RF
  //vw_set_ptt_inverted(true);  // Required by the RF module ---OBS REMOVE
  //vw_setup(2000);            // bps connection speed ---OBS
  //vw_set_rx_pin(18);         // RF pin ---OBS
  //vw_rx_start();
}

void loop()
{
  
// Availability Message
   //Serial.print(sensorReading);
   //sensorReading = analogRead(knockSensor);
   //if (sensorReading >= calibracao) {
   //Serial.println("Knock!");                   
   //}
   //delay(1000);
                        
    if (rfid.isCard()) {
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
                        // Start of card verification
                        if(rfid.serNum[0] == 137) {
                          Serial.println("Admin User");
                          validUser = 1;
                        } else if(rfid.serNum[0] == 43) {
                          Serial.println("User");
                          validUser = 1;
                        }
                        // End of verification
                        if (validUser == 1){
                          
                        Serial.println("Sistema ativo");
                        while (option == 0){
                        // Painel de selecao
                        // Button1
                        button1State = digitalRead(button1);
                        if (button1State == LOW) {  
                        //MP3player.playTrack(1);
                          Serial.println("Botao1 pressionado");
                          option = 1;
                        } else {
                          Serial.println("Botao1 nao pressionado");
                        }
                        }
                        // Button2
                        //button2State = digitalRead(button2);
                        //if (button2State == LOW) {  
                        //  MP3player.playTrack(2);
                        //Serial.println("Botao2 pressionado");
                        //}
                        //else {
                        //  Serial.println("Botao2 nao pressionado");
                        //}
                        
                        // Button3
                        //button3State = digitalRead(button3);
                        //if (button3State == LOW) {  
                        //  MP3player.playTrack(1);
                        //Serial.println("Botao3 pressionado");
                        //}
                        //else {
                        //  Serial.println("Botao3 nao pressionado");
                        //}
                        }
           delay(1000);
    }
    
    rfid.halt();
    
// Notification System
}
  if (waiting == true){
    if(option == 1){
      //Mensagem Opcao 1
      
      uint8_t buf[VW_MAX_MESSAGE_LEN];
      uint8_t buflen = VW_MAX_MESSAGE_LEN;
      if (vw_get_message(buf, &buflen)){
      int i;
      // Message with proper check    
      for (i = 0; i < buflen; i++){
       Serial.write(buf[i]);
          }
      Serial.println();
                       
      }
    }
    if(option == 2){
     //Mensagem Opcao 2
    }
    if(option == 3){
     //Mensagem Opcao 3
    }
  }
  else {
  option = 0;
  }
}
