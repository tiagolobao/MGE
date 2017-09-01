#include <Math.h>
unsigned long tempoV1=0;  //Tempos que irão mexer diretamente com os timers, por isso tem que ser do tipo unsigned. V referente a tensão, I referente a corrente.
unsigned long tempoV2=0;
unsigned long tempoI1=0;
unsigned long tempoI2=0;
float V = 0; //Tensão e corrente em valores eficazes
float I = 0;
float Vp = 0; //Tensão e correntes de pico
float Ip = 0;
float Vaux = 0; //Variáveis auxiliares para determinação da tensão e corrente de pico
float Iaux = 0;
float FV = 0; //Frequências da corrente e tensão. Devem dar muito próximas ou algo de errado não esta certo.
float FI = 0;
int contV = 1; //Contadores pra determinar picos diferentes;
int contI = 1;
int estadoV = 0; //Estados para determinar se a corrente e tensão estão no semi-ciclo ascendente ou descendente
int estadoI = 0;
double Fpot = 0; //Fator de potência ativa
double FpotR = 0;//Fator de potência reativa
float S = 0; //Potência Aparente
float P = 0; //Potência Ativa
float Q = 0; //Potência Reativa
float TV = 1; //Períodos referentes a tensão e corrente. Devem dar muito próximos ou algo de errado não está certo
float TI = 1;
float defasagem = 0; //Variável para calculo da defasagem tensão/corrente

void setup() {

pinMode(A0,INPUT);
pinMode(A2,INPUT);
delay(1);
//Serial.begin(9600)  Caso Queiram conferir algo no serial monitor. NAO USEM NO CODIGO FINAL, SO VAI DEIXAR MAIS LENTO
Vaux = analogRead(A0);
Iaux = analogRead(A2);
if (analogRead(A0)>Vaux){
  estadoV = 0;
  }
  else{
    if (analogRead(A0)>Vaux){
  estadoV = 1;
  }
  }
 if (analogRead(A2)>Iaux){
 estadoI = 0;
 }
  else{
    if (analogRead(A2)<Iaux){
    estadoI = 1;
    }
  }
}

void loop() {

Vaux = analogRead(A0);
Iaux = analogRead(A2);
Vaux = Vaux*(5.0/1024.0) // Aplicação do fator de escala, vai ser sempre X/1024, onde 1024 vai ser a leitura maxima do arduino, 5Volts,
                         // E o numerador Deve ser o valor DE PICO! real da amostra de calibração que estamos medindo que deverá gerar 5 Volts pro arduino.
Iaux = Iaux*(5.0/1024.0) // Lembrem SEMPRE de por um ".0" após o numero se ele for inteiro, pra evitar Bugs de divisão.

  //As duas medições ja foram feitas, logo, embora não simultâneas, já temos elas feitas os mais próximo possível uma da outra.
  //O tratamento dos valores da tensão começa aqui
  if(estadoV == 0){
    if(Vaux>Vp){
    Vp = Vaux;
    }
    else{
    if(Vaux<Vp){
    V = Vp/1.4142;
    Vp = Vaux;
    //INSERIR AQUI O COMANDO PARA ENVIAR O VALOR DA TENSAO (V) PRO ESP ||||||||||||||||
    // //INSERIR AQUI COMANDOS DE SERIAL PRINT, SE DESEJAREM VER A TENSAO NO SERIAL MONITOR
       if (contV==1){
        tempoV1 = micros();
        }
        if (contV==2){
        tempoV2 = micros();
        TV = (tempoV2-tempoV1);
        TV = abs(TV);
        FV = 1000000.0/TV;
        //INSERIR AQUI O COMANDO PARA ENVIAR O VALOR DA FREQUENCIA (FV) PRO ESP |||||||||||||||||||||||||
        //INSERIR AQUI COMANDOS DE SERIAL PRINT, SE DESEJAREM VER A FREQUENCIA NO SERIAL MONITOR
        contV = 0;
        }
      contV=contV+1;
      estadoV = 1;
    }
  }
  }
  if (estadoV==1){
    if(Vaux<Vp){
    Vp = Vaux;
    }
    else{
      if(Vaux>Vp){
      estadoV=0;
      Vp = Vaux;
      }
    }
  }


  //O tratamento dos valores de corrente começa aqui
  if(estadoI == 0){
    if(Iaux>Ip){
    Ip = Iaux;
    }
    else{
    if(Iaux<Ip){
    I = Ip/1.4142;
    Ip = 0;
    //INSERIR AQUI O COMANDO PARA ENVIAR O VALOR DA CORRENTE (I) PRO ESP||||||||||||||||||||||||
     //INSERIR AQUI COMANDOS DE SERIAL PRINT, SE DESEJAREM VER A CORRENTE NO SERIAL MONITOR
       if (contI==1){
        tempoI1 = micros();
        }
        if (contI==2){
        tempoI2 = micros();
        TI = (tempoI2 - tempoI1);
        TI = abs(TI);
        FI = 1000000.0/TI;
        //INSERIR AQUI O COMANDO PARA ENVIAR O VALOR DA FREQUENCIA (FI) PRO ESP||||||||||||||||||
        //INSERIR AQUI COMANDOS DE SERIAL PRINT, SE DESEJAREM VER A FREQUENCIA NO SERIAL MONITOR
        contI = 0;
        }
      contI=contI+1;
      estadoI = 1;
    }
  }
  }
  if (estadoI==1){
    if(Iaux<Ip){
    Ip = Iaux;
    }
    else{
      if(Iaux>Ip){
      estadoI=0;
      Ip = Iaux;
      }
    }
  }

//Aqui se inicia o tratamento dos dados que envolvem tensao e corrente casados.
defasagem = (tempoV1 - tempoI1);
defasagem = abs(defasagem);
if(defasagem < TV){ //Filtragem simples pra evitar dados esdruxulos por conta do estouro do timer que a função micros() usa. Basicamente diz que a defasagem so representa algo válido se for menor que o período.
defasagem = defasagem*6.2832/TV;
Fpot = sin(defasagem);
FpotR = cos(defasagem);
S = V*I;
P = S*Fpot;
Q = S*FpotR;
//ENVIA AQUI OS VALORES DE FPOT,FPOTR, S,P e Q PRO ESP.
//INSERIR AQUI COMANDOS DE SERIAL PRINT, SE DESEJAREM VER QUALQUER UMA DESSAS GRANDEZAS NO SERIAL MONITOR
}
}
//CABOU CÓDIGO, UFA!
