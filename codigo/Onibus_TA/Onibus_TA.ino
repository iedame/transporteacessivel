// Bibliotecas
#include <VirtualWire.h> // RF
// Inicializacoes
const int button1 = 9; // A0
const int buzzer = 3;
int button1State = 0; // Estado inicial desligado
// Setup
void setup()
{
    Serial.begin(9600);  
    pinMode(button1, INPUT);
    pinMode(buzzer, OUTPUT);
    beep(50);
    beep(50);
    beep(50);
    vw_set_ptt_inverted(true);  // Necessario para o modulo RF
    vw_setup(2000);            // Velocidade de conexao em bps
    vw_set_tx_pin(5);         // Pino do Arduino conectado a Data
}
// Loop 
void loop()
{
  button1State = digitalRead(button1);
  if (button1State == LOW) { 
     //Message to send:
   beep(200);
   beep(200);
   const char *msg = "701U10PARADA"; // Identificador do onibus transmitido
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();        // Espera a mensagem ser enviada
   Serial.println("Parada");
   delay(200);         // Espera antes de enviar a mensagem novamente  
  }
  else {
   //Message to send:
   const char *msg = "701U10"; // Identificador do onibus transmitido
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();        // Espera a mensagem ser enviada
   Serial.println("Chegada");
   delay(200);         // Espera antes de enviar a mensagem novamente  
  }   
}

void beep(unsigned char delayms){
  analogWrite(buzzer, 20);      // Almost any value can be used except 0 and 255
  delay(delayms);          // wait for a delayms ms
  analogWrite(buzzer, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}
