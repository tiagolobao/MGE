void buildWebsite(){
html = "<!DOCTYPE html>\n\
<html>\n\
\n\
  <head>\n\
\n\
  <script src=\"https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script>\n\
  <script>\n\
  var xmlHttp=createXmlHttpObject();\n\
\n\
  function createXmlHttpObject(){\n\
   if(window.XMLHttpRequest){\n\
      xmlHttp=new XMLHttpRequest();\n\
   }else{\n\
      xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n\
   }\n\
   return xmlHttp;\n\
 }\n\
\n\
  function process(){\n\
   if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n\
     xmlHttp.open('PUT','xml',true);\n\
     xmlHttp.onreadystatechange=handleServerResponse;\n\
     xmlHttp.send(null);\n\
   }\n\
   setTimeout('process()',1000);\n\
 }\n\
\n\
  function handleServerResponse(){\n\
   if(xmlHttp.readyState==4 && xmlHttp.status==200){\n\
     xmlResponse=xmlHttp.responseXML;\n\
     xmldoc = xmlResponse.getElementsByTagName('response');\n\
     message = xmldoc[0].firstChild.nodeValue;\n\
     document.getElementById('runtime').innerHTML=message;\n\
   }\n\
 }\n\
  </script>\n\
\n\
\n\
  </head>\n\
\n\
  <body onload='process()'>\n\
  <br>This is the ESP website ...<br>\n\
  Runtime = <a id='runtime'></a>\n\
  <div>\n\
  </div>\n\
  </body>\n\
\n\
   <script>\n\
     $.get(\"localhost/esp.html\", function(data){\n\
      $(this).children(\"div:first\").html(data);\n\
     });\n\
   </script>\n\
</html>";
}



void buildXML(){
  XML="<?xml version='1.0'?>";
  XML+="<response>";
  XML+=millis2time();
  XML+="</response>";
}

