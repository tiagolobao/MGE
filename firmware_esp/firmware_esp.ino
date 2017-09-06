#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid="senha da wifi";
const char* password="senha";
String html,XML;
float data[5];


/* Obtenção das informações coletadas via serial */
void getData(){
  if(Serial.available()){
    while(Serial.read() != 'F');
    for(int i=0; i<4; i++){
      while(!Serial.available());
      data[i]=Serial.parseFloat();
    }
    for(int i=0; i<4; i++){
      Serial.println(data[i]);
    }
    Serial.flush();
  }
}

/* METODO GET */
void handleWebsite(){
  buildWebsite();
  server.send(200,"text/html",html);
}

/* METODO PUT (AJAX) */
void handleXML(){
  buildXML();
  server.send(200,"text/xml",XML);
}

void setup() {
  //Inicialização
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  //Printa no serial monitor o status e o IP
  Serial.println("\n\nBOOTING ESP8266 ...");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Station IP address: ");
  Serial.println(WiFi.localIP());

  //Configura os endereços para cada requisição
  server.on("/",handleWebsite);
  server.on("/xml",handleXML);

  //Inicializa o servidor
  server.begin();
}

void loop() {
  server.handleClient();
  getData();
}
