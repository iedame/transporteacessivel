// Bibliotecas
#include <VirtualWire.h> // RF
// Inicializacoes
const int button1 = 5; //
int button1State = 0; // Estado inicial desligado
// Setup
void setup()
{
    pinMode(button1, INPUT);
    vw_set_ptt_inverted(true);  // Necessario para o modulo RF
    vw_setup(2000);            // Velocidade de conexao em bps
    vw_set_tx_pin(3);         // Pino do Arduino conectado a Data
}
// Loop 
void loop()
{
  button1State = digitalRead(button1);
  if (button1State == LOW) { 
     //Message to send:
   const char *msg = "701U10STOP"; // Identificador do onibus transmitido
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();        // Espera a mensagem ser enviada
   delay(200);         // Espera antes de enviar a mensagem novamente  
  }
  else {
   //Message to send:
   const char *msg = "701U10"; // Identificador do onibus transmitido
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();        // Espera a mensagem ser enviada
   delay(200);         // Espera antes de enviar a mensagem novamente  
  }   
}
