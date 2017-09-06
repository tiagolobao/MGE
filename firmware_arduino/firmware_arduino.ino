#include <EmonLib.h>                                  // inclue a biblioteca que calcula a tensão

EnergyMonitor emon1;                                   // Cria uma instancia

float dados[5];
char i;
//Realiza as configurações iniciais
void setup() {
 Serial.begin(115200);                                           //  Comunicação serial a 9600 bits por segundo
 emon1.voltage(A0, 135.0, 0);                 //  Entrar com pino do Arduino,Voltagem da rede e defasagem 64.67  77.6
 emon1.current(A2, 4.0);                                          // Entrar com  pino do Arduino, Constante do sensor de corrente
}

//Função principal de operação. Repetida infinitas vezes a partir do momento que a função de configuração termina.
void loop() {
 i=0;
 emon1.calcVI(40, 4000);                              //(crossings,timeout)
 //emon1.serialprint();                                 // Imprime na serial todos os valores calculados
 dados[3] = abs(emon1.realPower);         //recebe potência Ativa
 //dados[1] = emon1.apparentPower;     //recebe potência Aparente
 dados[2] = abs(emon1.powerFactor);       //recebe fator de potência
 dados[0] = emon1.Vrms;              //recebe Tensão rms
 dados[1] = emon1.Irms;         //recebe Corrente rms
 Serial.print('F');
 while (i < 4) {
   Serial.print(dados[i]);
   Serial.print(" ");
   i++;
 }
}
