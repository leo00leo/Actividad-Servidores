#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <Wifi.h>


const char* ssid = "CESJT";
const char* password = "itisjtsmg";

AsyncWebServer server(80);

int ventilador = 5; 
int lento = 50;
int medio = 150;
int alto = 255;

const char venti[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>CONTROL DE VENTILADOR</title>
  <style>
    html { font-family: Arial black; text-align: center;color: #2b3d4f; }
    .btn { display: inline-block; background-color: #c0392b; border: none; color: #ecf0f1;
           padding: 16px 30px; text-decoration: none; font-size: 24px; margin: 2px; cursor: pointer; border-radius: 8px; height: 20vh; width: 180px; }
    .btn-low { background-color: #2980b9; }
    .btn-medium { background-color: #27ae60; }
    .btn-high { background-color: #f39c12; }
  </style>
</head>
<body>
    <span><h1>CONTROL DE VENTILADOR</h1>
    <p> 
        <a href="/vecac"><button class="btn">VELOCIDADACTUAL</button></a>
    </p>  
    <p> 
        <a href="/off"><button class="btn">APAGADO</button></a>
    </p>
    <p>
        <a href="/low"><button class="btn btn-low">BAJO</button></a>
    </p>
        <a href="/medium"><button class="btn btn-medium">MEDIO</button></a>
    </p>
    <p>
        <a href="/high"><button class="btn btn-high">ALTO</button></a>
    </p>
    </span>

</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  //configuracion de pines
  pinMode(ventilador, OUTPUT);

  // conexion al wifi como antes
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout = 20; // 20 intentos de 500ms = 10 segundos
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFallo la conexion. Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: http://");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){
    String pagina = venti;

    //aca puedo desarrolar lo que quiero que pase en el server
    request -> redirect("/"); //envio de pagina de manera asincrona DUAAA
  });
  server.on("/high", HTTP_GET, [] (AsyncWebServerRequest *request){
    String pagina = venti;

    //aca puedo desarrolar lo que quiero que pase en el server
    pagina.replace("vecac", "high");
    analogWrite(ventilador, alto);
    request -> redirect("/"); //envio de pagina de manera asincrona
  });
  server.on("/medium", HTTP_GET, [] (AsyncWebServerRequest *request){
    String pagina = venti;

    //aca puedo desarrolar lo que quiero que pase en el server
    pagina.replace("vecac", "medium");
    analogWrite(ventilador, medio);

    request -> redirect("/"); //envio de pagina de manera asincrona
  });
  server.on("/low", HTTP_GET, [] (AsyncWebServerRequest *request){
    String pagina = venti;
    //aca puedo desarrolar lo que quiero que pase en el server
    pagina.replace("vecac", "low");
    analogWrite(ventilador, lento);

    request -> redirect("/"); //envio de pagina de manera asincrona
  });
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *request){
    String pagina = venti;
    //aca puedo desarrolar lo que quiero que pase en el server
    pagina.replace("vecac", "off");
    analogWrite(ventilador, 0);

    request -> redirect("/"); //envio de pagina de manera asincrona
  });
  

  server.begin();
}