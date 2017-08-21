#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid="Troco_senha_por_XBOX";
const char* password="senha";
String html,XML;
float data[5];

void getData(){
  if(Serial.available()){
    for(int i=0; i<4; i++){
      data[i]=Serial.parseFloat();
    }
    for(int i=0; i<4; i++){
      Serial.println(data[i]);
    }
    Serial.flush();
  }
}


String millis2time(){
  String Time="";
  unsigned long ss;
  byte mm,hh;
  ss=millis()/1000;
  hh=ss/3600;
  mm=(ss-hh*3600)/60;
  ss=(ss-hh*3600)-mm*60;
  if(hh<10)Time+="0";
  Time+=(String)hh+":";
  if(mm<10)Time+="0";
  Time+=(String)mm+":";
  if(ss<10)Time+="0";
  Time+=(String)ss;
  return Time;
}

void handleWebsite(){
  buildWebsite();
  server.send(200,"text/html",html);
}

void handleXML(){
  buildXML();
  server.send(200,"text/xml",XML);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  Serial.println("\n\nBOOTING ESP8266 ...");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Station IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleWebsite);
  server.on("/xml",handleXML);
  server.begin();
}

void loop() {
  server.handleClient();
  getData();
}
