// Bibliotecas
#include <SPI.h> // SPI Bus
#include <SdFat.h> // SD card
#include <SdFatUtil.h> // Utilitarios SD card
#include <SFEMP3Shield.h> // MP3 Shield
#include <RFID.h> // MF522-AN RFID
#include <VirtualWire.h> // RF

// Inicializacoes
RFID rfid(10,5); // Inicializa RFID (Pinos)
SdFat sd; // Inicializa SD
SFEMP3Shield MP3player; // Inicializa MP3 Shield

// Pinagem botoes do painel
const int button1 = 14; //A0
const int button2 = 15; //A1
const int button3 = 16; //A2

// Sensor piezo
const int knockSensor = A3; // Pino do sensor
const int calibracao = 6; // Valor de calibragem para ativacao
int sensorReading = 0; // Armazena valor lido no pino do sensor

// Botoes
int button1State = 0; // Estado inicial desligado
int button2State = 0; // - - -
int button3State = 0; // - - -

// Painel
int option = 0; // Armazena opcao selecionada no painel
int validUser = 0; // Armazena se usuario e valido
boolean waiting = false; // Verifica espera por onibus

// Setup
void setup()
{ 
  Serial.begin(9600); // abre porta serial, define taxa de dados em 9600 bps
  // RF
  //vw_set_ptt_pin(18);
  vw_set_ptt_inverted(true);  // Required by the RF module
  vw_setup(2000);            // bps connection speed
  vw_set_rx_pin(18);         // RF pin A4
  vw_rx_start();
  // SPI, RFID e MP3
  SPI.begin();
  rfid.init();
  sd.begin(SD_SEL, SPI_HALF_SPEED);
  MP3player.begin();
  MP3player.setDifferentialOutput(1);
  MP3player.setVolume(6, 6);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);  
  pinMode(button3, INPUT);
  
}

void loop()
{
  
// Availability Message
    sensorReading = analogRead(knockSensor);
    //Serial.println(sensorReading);
    if (sensorReading >= calibracao) {
      MP3player.playTrack(1);
      Serial.println("Transporte acessivel disponivel.");
      delay(2000);
      //MP3player.stopTrack();
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
                        button1State = digitalRead(button1);
                        button2State = digitalRead(button2);
                        button3State = digitalRead(button3);
                        // Button1
                        if (button1State == LOW) {  
                          MP3player.playTrack(3);
                          Serial.println(" (1) Voce selecionou a linha 701U/10, sentido centro.");
                          delay(5000);
                          option = 1;
                          waiting = true;
                        }
                        // Button2
                        if (button2State == LOW) {  
                          MP3player.playTrack(4);
                        Serial.println(" (2) Voce selecionou a linha 875A/10, sentido centro.");
                         delay(5000);
                         option = 2;
                         waiting = true;
                        }
                        // Button3
                        if (button3State == LOW) {  
                          MP3player.playTrack(5);
                        Serial.println(" (3) Voce selecionou a linha 702C/10, sentido centro.");
                         delay(5000);
                         option = 3;
                         waiting = true;
                        }
                        }
           delay(1000);
    }
    
    rfid.halt();
    
// Notification System
}
  if (waiting == true){
    if(option == 1){
      //Mensagem Opcao 1
       // RF
      while(waiting == true){
      uint8_t buf[VW_MAX_MESSAGE_LEN];
      uint8_t buflen = VW_MAX_MESSAGE_LEN;
      if (vw_get_message(buf, &buflen)) {
        int i;
        Serial.print("Got: ");
      // Message with proper check    
        for (i = 0; i < buflen; i++){
           Serial.print(buf[i], HEX);
           Serial.print(" ");
          }
      Serial.println();   
      waiting = false;      
      }
     else {
        Serial.println("nada enviado");
      }
     }
      MP3player.playTrack(6);
      Serial.println(" (1) O onibus 701U/10, sentido centro, esta se aproximando.");
      delay(5000);
      
      //waiting = false;
      option = 0;
    }
    if(option == 2){
     //Mensagem Opcao 2
     MP3player.playTrack(7);
     Serial.println(" (2) O onibus 875A/10, sentido centro, esta se aproximando.");
     delay(6000);
     waiting = false;
     option = 0;
    }
    if(option == 3){
     //Mensagem Opcao 3
     MP3player.playTrack(8);
     Serial.println(" (3) O onibus 702C/10, sentido centro, esta se aproximando.");
     delay(5000);
     waiting = false;
     option = 0;
    }
  }
  else {
  option = 0;
  }
 }
}
