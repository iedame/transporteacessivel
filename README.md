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

###4. Sensor na guia táctil (piezo element)
Um sensor piezo element conectado o negativo em GND e o positivo à porta A3 com um resistor de 1mOhm e 2 jumper wires.

| UNO  | Positivo | Negativo|
| ---- |:--------:| ----:|
| A3   | A3-1mOhm-GND |     |
| GND  |             |  GND  |

###5. RF transmitter XY-FST (315MHz)
Um receptor XY-RF-5V de 315MHz com 4 pinos dos quais 3 são utilizados.

| pins | UNO |
| ---- |:---:|
| GND  | GND |
| DATA | 03  |
| DATA |     |
| VCC  | +5V |

###6. No segundo Arduino, RF receiver XY-RF-5V (315MHz)
Um transmissor XY-FST de 315MHz com 3 pinos.

| pins | UNO  | Perna dir |
| ---- |:--------:| ----:|
| ATAD | 18(A4)   |  5V  |
| VCC  | +5V   |  5V  |
| GND  | GND   |  5V  |
