aTransportA: Acessible Transport using Arduino.
========================================================================
###Instruções de montagem

###1. SparkFun MP3 Shield
Este módulo é um shield, basta conectá-lo sobre o Arduino com os conectores empilháveis.

###2. MF522-AN RFID (13.56 Mhz)
Este módulo consiste da placa MF522-AN com 8 pinos (das quais utiliza-se 7) e 7 jumper wires. 

| Pins | SPI      | UNO  | Mega2560    |
| ---- |:--------:| ----:| --------:   |
| 1    | SS       |  10  |  53         |
| 2    | SCK      |  13  |  52         |
| 3    | MOSI     |  11  |  51         |
| 4    | MISO     |  12  |  50         |
| 5    |          | None               |
| 6    |          | GND                |
| 7    |          | RST (Digital Pin 5)|
| 8    |          | +3.3V              |

###3. Botões do painel de controle
Simplesmente conecte 3 botões utilizando 3 resistores pull-up de 10kOhms, 3 pushbuttons e 6 jumper wires.

| UNO (Perna esq) | Perna esq | Perna dir |
| ---- |:--------:| ----:|
|14(A0)| 10kOhm-GND   |  5V  |
|15(A1)| 10kOhm-GND   |  5V  |
|16(A2)| 10kOhm-GND   |  5V  |
