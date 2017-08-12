 #include <EmonLib.h>                                  // inclue a biblioteca que calcula a tensão

EnergyMonitor emon1;                                   // Cria uma instancia

float dados[5];
char i;
//Realiza as configurações iniciais
void setup() {
  Serial.begin(115200);                                           //  Comunicação serial a 9600 bits por segundo
  emon1.voltage(5, 38.8*2, 0);                 //  Entrar com pino do Arduino,Voltagem da rede e defasagem 64.67  77.6
  emon1.current(4, 5.7);                                          // Entrar com  pino do Arduino, Constante do sensor de corrente
}

//Função principal de operação. Repetida infinitas vezes a partir do momento que a função de configuração termina.
void loop() {
  i=0;
  emon1.calcVI(40, 4000);                              //(crossings,timeout)
  //emon1.serialprint();                                 // Imprime na serial todos os valores calculados
  dados[0] = emon1.realPower;         //recebe potência Ativa
  dados[1] = emon1.apparentPower;     //recebe potência Aparente
  dados[2] = emon1.powerFactor;       //recebe fator de potência
  dados[3] = emon1.Vrms;              //recebe Tensão rms
  dados[4] = 3*emon1.Irms;         //recebe Corrente rms
  while (i < 5) {
    Serial.print('A');
    Serial.print(dados[i]); 
    i++;
  }
}


