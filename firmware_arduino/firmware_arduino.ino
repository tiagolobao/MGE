  /* bibliotecas e definições */
#include <EmonLib.h>
#define SEND_MSG 'A'

/* Variáveis globais */
EnergyMonitor emon1;
float dados[5];
char i;


void setup() {
  Serial.begin(115200);
  //Configuração do objeto
  emon1.voltage(5, 38.8*2, 0);
  emon1.current(4, 5.7);
}


void loop() {
  i=0;
  emon1.calcVI(40, 4000);
  dados[0] = emon1.realPower;     //recebe potência Ativa
  dados[1] = emon1.apparentPower; //recebe potência Aparente
  dados[2] = emon1.powerFactor;   //recebe fator de potência
  dados[3] = emon1.Vrms;          //recebe Tensão rms
  dados[4] = 3*emon1.Irms;        //recebe Corrente rms
  /* Envio das informações para o ESP */
  while (i < 5) {
    Serial.print(SEND_MSG);
    Serial.print(dados[i]);
    i++;
  }
}
