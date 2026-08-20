#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

const int ledPin[5]={2,32,33,25,26
}; 
int animacion=0;
WebServer server(80);


bool ledANIMACION2 = true;
bool ledAPAGADO = true;

int animacion1 [3][5]={
  {0,0,0,0,0},//0
  {1,0,1,0,1},//1
  {0,1,0,1,0}//2
};

int animacion2 [3][5]={
  {1,1,1,1,1},//0
  {1,0,0,0,1},//1
  {0,1,1,1,0}//2
};

int apagado [1][5]={
  {0,0,0,0,0},//0

};

int apagar;
// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>  
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-color: black; text-align: center; }
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
    .boton { width: 80px; height: 45px; background-color: yellow; color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer; }
  </style>
</head>
<body>
  <h1 class='titulo'>ANIMACIONES</h1>
  <p><a href='/animacion1'><button class='boton'>ANIMACION1</button></a></p>
  <p><a href='/animacion2'><button class='boton'>ANIMACION2</button></a></p>
  <p><a href='/apagado'><button class='boton'>APAGADO</button></a></p>
</body>
</html>
)rawliteral";

void an1(){
  for(int i=0;i<3;i++){
    for(int j=0;j<5;j++){
        digitalWrite(ledPin[j],animacion1[i][j]);
      }
    delay(500);
  }
}
void an2(){
  for(int i=0;i<3;i++){
    for(int j=0;j<5;j++){
      digitalWrite(ledPin[j],animacion2[i][j]);
      
    }
    delay(500);
  }
}
void off(){
  for(int i=0;i<5;i++){
        digitalWrite(ledPin[i],LOW);
  }
  animacion=0;
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
}

void setup() {
  Serial.begin(115200);
  for(int i=0;i<5;i++){

    pinMode(ledPin[i], OUTPUT);
  }

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

  server.on("/", []() {
    

    server.send(200, "text/html", pagina_template);
  });

  server.on("/animacion1",[](){
    animacion=1;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/animacion2",[](){
    animacion=2;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/apagado",off);

  server.begin();
}

void loop() {
  server.handleClient();

  if(animacion==1) an1();
  else if(animacion==2) an2;
}

