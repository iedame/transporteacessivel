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
const int button1 = 14; //A0
const int button2 = 15; //A1
const int button3 = 16; //A2
// Piezo
const int knockSensor = A3; // Piezo ligado ao Pino analógico 3;
const int calibracao = 6; // Limite estabelecido para acionamento do aviso sonóro;
int sensorReading = 0; // Armazena valor lido no pino do sensor;
// Buttons
int button1State = 0;
int button2State = 0;
int button3State = 0;
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
  //vw_set_ptt_inverted(true);  // Required by the RF module
  //vw_setup(2000);            // bps connection speed
  //vw_set_rx_pin(18);         // RF pin
  //vw_rx_start();
}

void loop()
{
  
// Availability Message
    sensorReading = analogRead(knockSensor);
    //Serial.println(sensorReading);
    if (sensorReading >= calibracao) {
      //MP3player.playTrack(1);
      Serial.println("Transporte acessivel disponivel.");
      delay(2000);
    }
    
    if (rfid.isCard()) {
          if (rfid.readCardSerial()) {
            
                        Serial.println(" ");
                        Serial.println("Numero do cartao Mifare lido: ");
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
                          Serial.println("Usuario administrativo");
                          validUser = 1;
                          MP3player.playTrack(2);
                          delay(2000);
                        } else if(rfid.serNum[0] == 43) {
                          Serial.println("Usuario valido");
                          validUser = 1;
                        }
                        // End of verification
                        if (validUser == 1){
                          
                        Serial.println("Sistema ativo");
                        Serial.println("Aguardando escolha de linha...");
                        while (option == 0){
                        // Painel de selecao
                        // Button1
                        button1State = digitalRead(button1);
                        if (button1State == LOW) {  
                          MP3player.playTrack(3);
                          Serial.println(" (1) Voce selecionou a linha 701U/10, sentido centro.");
                          delay(5000);
                          option = 1;
                          waiting = true;
                        } else {
                          //Waiting for bus selection
                          //Serial.println("Botao1 nao pressionado");
                        }
                        }
                        // Button2
                        //button2State = digitalRead(button2);
                        //if (button2State == LOW) {  
                        //  MP3player.playTrack(4);
                        //Serial.println(" (2) Voce selecionou a linha 875A/10, sentido centro.");
                        // delay(5000);
                        //}
                        //else {
                        //  Serial.println("Botao2 nao pressionado");
                        //}
                        
                        // Button3
                        //button3State = digitalRead(button3);
                        //if (button3State == LOW) {  
                        //  MP3player.playTrack(5);
                        //Serial.println(" (3) Voce selecionou a linha 702C/10, sentido centro.");
                        // delay(5000);
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
      MP3player.playTrack(6);
      Serial.println(" (1) O onibus 701U/10, sentido centro, esta se aproximando.");
      delay(5000);
      //uint8_t buf[VW_MAX_MESSAGE_LEN];
      //uint8_t buflen = VW_MAX_MESSAGE_LEN;
      //if (vw_get_message(buf, &buflen)){
      //int i;
      // Message with proper check    
      //for (i = 0; i < buflen; i++){
       //Serial.write(buf[i]);
      //    }
      //Serial.println();                 
      //}
      waiting = false;
    }
    if(option == 2){
     //Mensagem Opcao 2
     MP3player.playTrack(7);
     Serial.println(" (2) O onibus 875A/10, sentido centro, esta se aproximando.");
     delay(6000);
    }
    if(option == 3){
     //Mensagem Opcao 3
     MP3player.playTrack(8);
     Serial.println(" (3) O onibus 702C/10, sentido centro, esta se aproximando.");
     delay(5000);
    }
  }
  else {
  option = 0;
  }
}