void buildWebsite(){
html = "<!DOCTYPE html> <html> <head> <meta name=viewport content=\"width=device-width, user-scalable=no\"> <script>var FP=0.5;var Av=127;var Ai=1;var xmlHttp=createXmlHttpObject();function createXmlHttpObject(){if(window.XMLHttpRequest){xmlHttp=new XMLHttpRequest()}else{xmlHttp=new ActiveXObject(\"Microsoft.XMLHTTP\")}return xmlHttp}function process(){if(xmlHttp.readyState==0||xmlHttp.readyState==4){xmlHttp.open(\"PUT\",\"xml\",true);xmlHttp.onreadystatechange=handleServerResponse;xmlHttp.send(null)}setTimeout(\"process()\",2000)}function handleServerResponse(){if(xmlHttp.readyState==4&&xmlHttp.status==200){xmlResponse=xmlHttp.responseXML;xmldoc=xmlResponse.getElementsByTagName(\"Av\");Av=xmldoc[0].firstChild.nodeValue;xmldoc=xmlResponse.getElementsByTagName(\"Ai\");Ai=xmldoc[0].firstChild.nodeValue;xmldoc=xmlResponse.getElementsByTagName(\"FP\");FP=xmldoc[0].firstChild.nodeValue;document.getElementById(\"v\").innerHTML=Av;document.getElementById(\"i\").innerHTML=Ai;document.getElementById(\"fp\").innerHTML=FP;xmldoc=xmlResponse.getElementsByTagName(\"w\");document.getElementById(\"w\").innerHTML=xmldoc[0].firstChild.nodeValue}}</script> <style>canvas{border-radius:30%}html{background:white;font-family:monospace}.title{margin:3% 10%;font-size:40px;color:white;background-color:#53605b;border-style:dashed;border-color:white;border-width:10px;border-radius:20px;box-shadow:10px 10px;-webkit-box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51);-moz-box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51);box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51)}.values{color:white;font-style:oblique;font-size:20px;border-spacing:20px;text-align:left}.osciloscope{background:#53605b;max-width:70%;margin:0 auto;border-radius:30px;border-color:#53605b;border-style:solid;border-width:30px;box-shadow:10px 10px;-webkit-box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51);-moz-box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51);box-shadow:12px 13px 25px 3px rgba(0,0,0,0.51)}#ten{color:#2eb246}#cor{color:#f44242}#team{color:#53605b}</style> </head> <body onload=process()> <div align=center class=title> Medicao de grandezas eletricas </div> <div class=osciloscope> <table class=values align=center> <tr> <td id=ten> Tensao: <a id=v>0</a> V </td> <td id=cor> Corrente: <a id=i>0</a> A </td> </tr> <tr> <td> Potencia: <a id=w>0</a> W </td> <td> Fator de Pot: <a id=fp>0</a> </td> </tr> </table> <table align=center> <tr> <td id=sketch-holder></td> </tr> </table> </div> <br><br> <div id=team align=center> Equipe: <br> Tiago Lobao, Lucas Menezes, Ryan Teixeira, Flavia Bacelar. </div> <script src=https:////cdnjs.cloudflare.com/ajax/libs/p5.js/0.5.8/p5.js></script> <script>var offset=0;var tMax=0;var T=1;var f=0.007;var k=0;var step=0.05;var t=0;var V=[];var I=[];var padding=10;function setup(){pixelDensity(1);  tMax=(windowWidth/2);var a=createCanvas((windowWidth/2),(windowHeight/3));a.parent(\"sketch-holder\");offset=a.height/2;background(255,0,200);fill(204,101,192,127);strokeWeight(3);frameRate(30)}function draw(){background(255);stroke(46,178,70);for(t=0;t<=tMax;t+=T){V[t]=adjustAmp(Av,0.0021)*sin(2*PI*f*t+k);line(t-1,V[t-1]+offset,t,V[t]+offset)}stroke(244,66,66);for(t=0;t<=tMax;t+=T){I[t]=adjustAmp(Ai,0.3)*sin(2*PI*f*t+k+((1-FP)*3.1));line(t-1,I[t-1]+offset,t,I[t]+offset)}for(var a=0;a<tMax;a++){}k=k+step}function windowResized(){resizeCanvas((windowWidth/2),(windowHeight/3));tMax=(windowWidth/2);offset=canvas.height/2}function adjustAmp(c,a){var b=0;b=(a*canvas.height)*c;return b};</script> </body> </html>";
}



void buildXML(){
  XML="<?xml version='1.0'?>";
  XML+="<response>";

  XML+="<Av>";
  XML.concat(data[0]);
  XML+="</Av>";

  XML+="<Ai>";
  XML.concat(data[1]);
  XML+="</Ai>";

  XML+="<FP>";
  XML.concat(data[2]);
  XML+="</FP>";

  XML+="<w>";
  XML.concat(data[3]);
  XML+="</w>";

  XML+="</response>";

}
