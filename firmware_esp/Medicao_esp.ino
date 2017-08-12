#include <ESP8266WiFi.h>                              // inclue a biblioteca do esp12

const char* ssid = "medicao2017";     //ssid da rede wifi
const char* password = "medicao2017";  //senha da rede wifi

boolean vf = false;

float realPower;
float apparentPower;
float powerFactor;
float Vrms;
float Irms;
float dados[5];
char i;

WiFiServer server(80);

float potencia_acumulada = 0;                         //  Variavel para calculo de consumo
float potencia_reativa = 0;                            //  Variavel para calculo de potência reativa

//Realiza as configurações iniciais
void setup() {
  Serial.begin(115200);                                           //  Comunicação serial a 9600 bits por segundo
  while (WiFi.status() != WL_CONNECTED) { //enquanto não conecta fica tentando
    delay(500);
    //Serial.print(".");
  }
  // inicializa o server
  server.begin();
  //Serial.println(WiFi.localIP());
}

//Função principal de operação. Repetida infinitas vezes a partir do momento que a função de configuração termina.
void loop() {
  i = 0;
  if (Serial.available() > 0 && Serial.read()=='A') {
    for (i = 0; i < 5; i++) {
      dados[i] = Serial.parseFloat();
      //Serial.print(dados[i]);
      //Serial.print(" ");
      vf = true;
    }
  }
  if (vf) {
    Serial.flush();
    realPower = dados[0];
    apparentPower = dados[1];
    powerFactor = dados[2];
    Vrms = dados[3];
    Irms = dados[4];
    for (i = 0; i < 5; i++) {
      //Serial.println();
      //Serial.print(dados[i]);
      //Serial.print(" ");
    }
    potencia_acumulada += realPower / 3600000;         // Calcula a potência acumulada
    potencia_reativa = sqrt((apparentPower * apparentPower) - (realPower * realPower)); // Calcula a potencia reativa

    //Envia uma resposta http com as informações do medidor.
    WiFiClient client = server.available();
    if (client) {
      //Serial.println("new client");
      if (client.available()) {
        String req = client.readStringUntil('\r');
        //Serial.println(req);
        client.flush();
        String buf = "";
        buf += "HTTP/1.1 200 OK\r\n";
        buf += "Content-Type: text/html\r\n";
        buf += "Connection: close\r\n";
        // e envia os valores do medidor formatados em HTML
        buf += "<!DOCTYPE HTML>\r\n";
        buf += "<html>\r\n";
        buf += "<meta http-equiv=\"refresh\" content=\"3\">\r\n"; // Atualiza  pagina
        buf += "<title>Medidor de Energia_Gilberto</title></head>\n\r\n";
        buf += "<h1><font color='#000033'>MEDIDOR DE CONSUMO DE ENERGIA</h1>\r\n";
        buf += "<hr />\r\n"; // Imprime uma linha
        buf += "<h3><font color='#330099'>Gersica, Othon e Pericles</h3>\r\n";
        buf += "<hr />\r\n"; // Imprime uma linha
        buf += "<br><B><font size='6'><font color='#990000'>Tensao RMS:  \r\n";
        client.print(buf);
        client.println(Vrms, 2);
        buf = "";
        buf += "<B>V\r\n";
        buf += "<br><B><font color='#006400'>Corrente RMS : \r\n";
        client.print(buf);
        client.println(Irms, 3);
        buf = "";
        buf += "<B>A\r\n";
        buf += "<br><B><font color='#990000'>Potencia Aparente: \r\n";
        client.print(buf);
        client.println(apparentPower);
        buf = "";
        buf += "<B>VA\r\n";
        buf += "<br><B><font color='#006400'>Potencia Ativa: \r\n";
        client.print(buf);
        client.println(realPower);
        buf = "";
        buf += "<B>W\r\n";
        buf += "<br><B><font color='#990000'>Potencia Reativa : \r\n";
        client.print(buf);
        client.println(potencia_reativa);
        buf = "";
        buf += "<B>VAR\r\n";
        buf += "<br><B><font color='#006400'>Fator de Potencia : \r\n";
        client.print(buf);
        client.println(powerFactor);
        buf = "";
        buf += "<p><a href=\"?function=atualizar\"><button>ATUALIZAR</button></a></p>\r\n";
        buf += "</html>\r\n";
        client.print(buf);
        client.flush();
      }
      delay(1); // Espera  um milisegundo
      client.stop(); // Fecha conexão
      //Serial.println("cliente desconectado");
    }
    vf = false;
  }
}
