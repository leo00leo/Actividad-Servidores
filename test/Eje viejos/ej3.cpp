#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

unsigned long t_delay_lento_rojo = 70000;
unsigned long t_delay_lento_amarillo = 3000;
unsigned long t_delay_lento_verde = 50000;
unsigned long t_delay_normie_rojo = 45000;
unsigned long t_delay_normie_amarillo = 2000;
unsigned long t_delay_normie_verde = 65000;
unsigned long t_delay_rapido_rojo = 20000;
unsigned long t_delay_rapido_amarillo = 1000;
unsigned long t_delay_rapido_verde = 40000;
unsigned long t_delay_emergencia=1500;

unsigned long t_previo=0;
unsigned long t_actual=0;

int estado=0;

const int rojo=15;
const int amarillo=4;
const int verde=5;

volatile int configuracion=0;

WebServer server(80);

bool titilar = true;

const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>  
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-image: url(https://tse2.mm.bing.net/th/id/OIP.MnB7ulD1mGs6sTYK5b2l6gHaEK?r=0&rs=1&pid=ImgDetMain&o=7&rm=3); text-align: center; }
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
    .boton { width: 100px; height: 105px; background-color: rgb(245, 245, 239); color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer; }
  </style>
</head>
<body>
  <h1 class='titulo'>SEMAFORO  </h1>
  <p><a href='/cambio_display'><button class='boton'>__CAMBIAR_DISPLAY__</button></a></p>
  <a href='/1'><button class='boton' style='background-color: red; color: rgb(1, 1, 1);'>LENTO</button></a>
  <p><a href='/7'><button class='boton' style='background-color: yellow; color: rgb(1, 1, 1);'>NORMAL</button></a>
  <p><a href='/7'><button class='boton' style='background-color: rgb(0, 255, 21); color: rgb(1, 1, 1);'>RAPIDO</button></a>
  <p><a href='/0'><button class='boton'>EMERGENCIA</button></a></p>
</body>
</html> 
)rawliteral";


void setup() {
  Serial.begin(115200);
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);

  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout = 20; 
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

  server.on("/1",[](){
    configuracion=1;
    server.sendHeader("Location", "/");            
    server.send(302, "text/plain", ""); 
  });

  server.on("/2",[](){
    configuracion=2;
    server.sendHeader("Location", "/");          
    server.send(302, "text/plain", "");
  });

  server.on("/3",[](){
    configuracion=3;
    server.sendHeader("Location", "/");      
    server.send(302, "text/plain", "");
  });

  server.on("0",[](){
    configuracion=4;
    server.sendHeader("Location", "/");           
    server.send(302, "text/plain", "");
  });

  server.begin();
}


void loop() {
  server.handleClient();
  switch (configuracion) {
    case 1: 
      if(estado==0 && t_actual-t_previo>=t_delay_lento_rojo) {
        estado=1;
         t_previo=t_actual;
        } else if (estado==1 && t_actual-t_previo>=t_delay_lento_amarillo) {
          estado=2;
          t_previo=t_actual;
        } else if (estado==2 && t_actual-t_previo>=t_delay_lento_verde) {
          estado=0;
          t_previo=t_actual;
      }
    break;

    case 2:
      if (estado==0 && t_actual-t_previo>=t_delay_normie_rojo) {
        estado=1;
        t_previo=t_actual;
      } else if (estado==1 && t_actual-t_previo>=t_delay_normie_amarillo) {
        estado=2;
        t_previo=t_actual;
      } else if (estado==2 && t_actual-t_previo>=t_delay_normie_verde) {
        estado=0;
        t_previo=t_actual;
      }
    break;

    case 3:
      if (estado==0 && t_actual-t_previo>=t_delay_rapido_rojo) {
        estado=1;
        t_previo=t_actual;
        } else if (estado==1 && t_actual-t_previo>=t_delay_rapido_amarillo) {
          estado=2;
          t_previo=t_actual;
        } else if (estado==2 && t_actual-t_previo>=t_delay_rapido_verde) {
          estado=0;
          t_previo=t_actual;
        }
    break;

    case 4:
            if (t_actual - t_previo >= t_delay_emergencia) {
            t_previo = t_actual;
            titilar!=titilar;
            if(titilar) estado=1;
            else estado=3;
            }
            break;

    default:
            break;
    }
  
}