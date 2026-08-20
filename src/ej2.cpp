#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

String display_boton="2", num_display_actual="1",fondo="__FONFO.jpg";
int display_act=1, num=0;


const int pind7s1[7]={32,33,25,26,27,14,12};
const int pind7s2[7]={32,33,25,26,27,14,12};
const int d7s[10][7]={
//   a,b,c,d,e,f,g
    {1,1,1,1,1,1,0},//0
    {0,1,1,0,0,0,0},//1
    {1,1,1,1,0,0,1},//2
    {0,1,1,0,0,0,0},//3
    {0,1,1,0,0,1,1},//4
    {0,0,1,1,0,1,1},//5
    {1,0,1,1,1,1,1},//6
    {1,1,1,0,0,0,0},//7
    {1,1,1,1,1,1,1},//8
    {1,1,1,1,0,1,1} //9
};


int numerador=0;
int ds7=0;
WebServer server(80);

bool ledEncendido = true;

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>  
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-image: url(https://tse2.mm.bing.net/th/id/OIP.MnB7ulD1mGs6sTYK5b2l6gHaEK?r=0&rs=1&pid=ImgDetMain&o=7&rm=3); text-align: center; }
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
    .boton { width: 80px; height: 45px; background-color: yellow; color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer; }
  </style>
</head>
<body>
  <h1 class='titulo'>MANEJO DE 2 DISPLAY 7 SEGMENTOS</h1>
  <p><a href='/cambio_display'><button class='boton'>__CAMBIAR_DISPLAY__</button></a></p>
  <p><a href='/1'><button class='boton'>1</button></a><a href='/3'><button class='boton'>2</button></a><a href='/3'><button class='boton'>3</button></a></p>
  <p><a href='/4'><button class='boton'>4</button></a><a href='/6'><button class='boton'>5</button></a><a href='/6'><button class='boton'>6</button></a></p>
  <p><a href='/7'><button class='boton'>7</button></a><a href='/9'><button class='boton'>8</button></a><a href='/9'><button class='boton'>9</button></a></p>
  <p><a href='/0'><button class='boton'>0</button></a></p>
  <span>Display __NUMERO_DISPLAY_ACTUAL__</span>
</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);
  for(int i=0;i<7;i++){
  pinMode(pind7s1[i],OUTPUT);
  pinMode(pind7s2[i],OUTPUT);
  };
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
    
    String pagina=pagina_template;
    pagina.replace("__CAMBIAR_DISPLAY__",display_boton);
    pagina.replace("__NUMERO_DISPLAY_ACTUAL__",num_display_actual);
    //pagina.replace("__FONDO__",fondo);
    server.send(200, "text/html", pagina);
  });

  server.on("/cambio_display",[](){
    if(display_act==1){ 
    display_act=2; display_boton="1"; num_display_actual="2"; }
    else {display_act=1; display_boton="2"; num_display_actual="1";}
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/1",[](){
    num=1;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/2",[](){
    num=2;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/3",[](){
    num=3;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/4",[](){
    num=4;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/5",[](){
    num=5;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/6",[](){
    num=6;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/7",[](){
    num=7;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/8",[](){
    num=8;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/9",[](){
    num=9;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.on("/0",[](){
    num=0;
    server.sendHeader("Location", "/");
    server.send(302, "text/plain", ""); // 302 y send Header para que no me quede en /header
  });
  server.begin();
}

void loop() {
  server.handleClient();
    for(int i=0;i<7;i++) {
       // if(display_act==1) digitalWrite(pind7s1[i],d7s[num][i]);
       // else digitalWrite(pind7s2[i],d7s[num][i]);
    }
  
}